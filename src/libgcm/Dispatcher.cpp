#include "Dispatcher.hpp"

using namespace gcm;

void Dispatcher::distributeProcessors(const Task &task, const uint numberOfWorkers) {
	
	// distribute in the zeros guess
	initializeProcVSblock(task, numberOfWorkers);
	
	// apply two correctors iteratively
	while(correctMaxLoadedMostShared());
	while(correctMaxLoadedMinLoaded());
}

void Dispatcher::getProportionsOfBlockDivision(const uint blockId, 
                                               std::map<int, real>& proportions) {
	proportions.clear();
	assert( procVSblock.begin()->second.find(blockId)
	                != procVSblock.begin()->second.end() );
	for(auto p = procVSblock.begin(); p != procVSblock.end(); p++)
		if(p->second.at(blockId) != 0)
			proportions.emplace(p->first, p->second.at(blockId));
}

void Dispatcher::initializeProcVSblock(const Task& task, const uint numberOfWorkers) {
	// reduce computational costs of blocks to one standard
	std::vector<BlockProperties> blocks;
	for(auto body = task.bodies.begin(); body != task.bodies.end(); body++) {
		real sumOfBlockCosts = 0;
		for(auto block = body->blocks.begin(); block != body->blocks.end(); block++)
			sumOfBlockCosts += block->computationalCost;
		
		for(auto block = body->blocks.begin(); block != body->blocks.end(); block++) {
			BlockProperties blockProp = *block;
			blockProp.computationalCost = block->computationalCost / sumOfBlockCosts
			                            * body->computationalCost;
			blocks.push_back(blockProp);
		}
	}
	std::sort(blocks.rbegin(), blocks.rend());
	uint numberOfblocks = blocks.size();
	
	// initialize maps
	for(uint procId = 0; procId < numberOfWorkers; procId++) {
		std::map<uint, real> tmp;
		for(auto block = blocks.begin(); block != blocks.end(); block++)
			tmp.emplace(block->id, 0.0);
		procVSblock.emplace((int) procId, tmp);
	}
	
	real totalCost = 0;
	for (uint i = 0; i < numberOfblocks; i++)
		totalCost += blocks[i].computationalCost;
	
	// share processors among blocks in the zeroth guess:
	// divide every block among its workers equally
	for (uint i = 0; i < numberOfblocks; i++) {
		uint procPerblock = round(numberOfWorkers * 
		                         blocks[i].computationalCost / totalCost);
		if (procPerblock == 0) procPerblock = 1;
		for (uint j = 0; j < procPerblock; j++) {
			int minLoadedProcId; uint number; real minLoad;
			findMinLoadedProcId(minLoadedProcId, number, minLoad);
			procVSblock.at(minLoadedProcId).at(blocks[i].id) = 
			                    blocks[i].computationalCost / procPerblock;
		}
	}
}

int Dispatcher::correctMaxLoadedMostShared() {
	uint numberOfWorkers = procVSblock.size();
	
	int maxLoadedProcId; uint number; real maxProcLoad;
	findMaxLoadedProcId(maxLoadedProcId, number, maxProcLoad);
	real averageProcLoad = 0;
	for(auto p = procVSblock.begin(); p != procVSblock.end(); p++) {
		real procLoad = 0;
		for(auto b = p->second.begin(); b != p->second.end(); b++)
			procLoad += b->second;
		averageProcLoad += procLoad / numberOfWorkers;
	}
	if ( maxProcLoad - averageProcLoad < averageProcLoad / 10 )
		return 0;
	
	// find the most shared block among blocks of the most loaded worker
	uint maxNumberOfSharingProcessors = 0;
	uint mostSharedBlockId;
	for (auto b = procVSblock.at(maxLoadedProcId).begin(); 
	          b != procVSblock.at(maxLoadedProcId).end(); b++)
		if (b->second != 0) {
			uint numberOfSharingProcessors = 0;
			for (auto p = procVSblock.begin(); p != procVSblock.end(); p++)
				numberOfSharingProcessors += (p->second.at(b->first) != 0);
			if (numberOfSharingProcessors > maxNumberOfSharingProcessors) {
				maxNumberOfSharingProcessors = numberOfSharingProcessors;
				mostSharedBlockId = b->first;
			}
		}
	if (maxNumberOfSharingProcessors == 1)
		return 0;
	
	// correct division parts of the found block in order to
	// balance load among the workers of the block
	real a = procVSblock.at(maxLoadedProcId).at(mostSharedBlockId);
	real e = - a;
	for (auto b = procVSblock.at(maxLoadedProcId).begin(); 
	          b != procVSblock.at(maxLoadedProcId).end(); b++)
		e += b->second;
	real d = 0;
	for (auto p = procVSblock.begin(); p != procVSblock.end(); p++)
		if (p->first != maxLoadedProcId)
			d += p->second.at(mostSharedBlockId) / (maxNumberOfSharingProcessors - 1);
	real c = 0;
	for (auto p = procVSblock.begin(); p != procVSblock.end(); p++) {
		if ( (p->second.at(mostSharedBlockId) != 0) && (p->first != maxLoadedProcId) ) {
			for (auto b = p->second.begin(); b != p->second.end(); b++) {
				if (b->first != mostSharedBlockId)
					c += b->second / (maxNumberOfSharingProcessors - 1);
			}
		}
	}
			
	real x = (a + e - c - d) / maxNumberOfSharingProcessors;
	
	if (x / procVSblock.at(maxLoadedProcId).at(mostSharedBlockId) < 0.05)
		return 0;
	
	for (auto p = procVSblock.begin(); p != procVSblock.end(); p++)
		if (p->second.at(mostSharedBlockId) != 0)
			p->second.at(mostSharedBlockId) += x;
	procVSblock.at(maxLoadedProcId).at(mostSharedBlockId) -= 
	                                   maxNumberOfSharingProcessors * x;
	
	return 1;
}

int Dispatcher::correctMaxLoadedMinLoaded() {
	int maxId; uint numberOfMaxLoaded; real maxLoad;
	findMaxLoadedProcId(maxId, numberOfMaxLoaded, maxLoad);
	int minId; uint numberOfMinLoaded; real minLoad;
	findMinLoadedProcId(minId, numberOfMinLoaded, minLoad);
	if (numberOfMinLoaded < numberOfMaxLoaded) return 0;
	uint mostSuitableBlockId = -1;
	
	// find the block calculated by maxId and not calculated by minId
	// and the most suitable to move from maxId to minId
	for(auto b = procVSblock.at(maxId).begin(); b != procVSblock.at(maxId).end(); b++)
		if ( (b->second != 0) && (procVSblock.at(minId).at(b->first) == 0) ) {
			if (mostSuitableBlockId == (uint) (-1))
					mostSuitableBlockId = b->first;
			else if ( fabs(b->second - (maxLoad - minLoad)) < 
					  fabs(procVSblock.at(maxId).at(mostSuitableBlockId) - (maxLoad - minLoad)) )
					mostSuitableBlockId = b->first;
		}
	if (mostSuitableBlockId == (uint) (-1)) return 0;
	
	real haveToMove = ((maxLoad - minLoad) / 2) * 0.99999; 
	if (haveToMove < 0.2 * maxLoad) {
		return 0;
	}
	else if (haveToMove < procVSblock.at(maxId).at(mostSuitableBlockId)) {
		procVSblock.at(maxId).at(mostSuitableBlockId) -= haveToMove;
		procVSblock.at(minId).at(mostSuitableBlockId) += haveToMove;
	}
	
	return 1;
}

void Dispatcher::findMinLoadedProcId(int &id, uint &number, real &minLoad) {
	minLoad = std::numeric_limits<real>::infinity();
	for(auto p = procVSblock.begin(); p != procVSblock.end(); p++) {
		real load = 0;
		for(auto b = p->second.begin(); b != p->second.end(); b++)
			load += b->second;
		if (load < minLoad) {
			minLoad = load;
			id = p->first;
			number = 0;
		} else if (load == minLoad)
			number += 1;
	}
}

void Dispatcher::findMaxLoadedProcId(int &id, uint &number, real &maxLoad) {
	maxLoad = - 1;
	for(auto p = procVSblock.begin(); p != procVSblock.end(); p++) {
		real load = 0;
		for(auto b = p->second.begin(); b != p->second.end(); b++)
			load += b->second;
		if (load > maxLoad) {
			maxLoad = load;
			id = p->first;
			number = 0;
		} else if (load == maxLoad)
			number += 1;
	}
}

bool Dispatcher::isLoadBalanced() {
	real averageLoad = 0;
	real maxLoad = 0;
	for(auto p = procVSblock.begin(); p != procVSblock.end(); p++) {
		real load = 0;
		for(auto b = p->second.begin(); b != p->second.end(); b++)
			load += b->second;
		averageLoad += load / procVSblock.size();
		if (load > maxLoad)
			maxLoad = load;
	}
	if( (maxLoad - averageLoad) / averageLoad < 0.5 ) return true;
	else return false;
}

void Dispatcher::printProcVSblock() {
	std::cout << "======================================================================\nid = \t";
	for (auto b = procVSblock.begin()->second.begin(); 
	          b != procVSblock.begin()->second.end(); b++)
		std::cout << b->first << "\t";
	std::cout << "\n----------------------------------------------------------------------\n";
	for (auto p = procVSblock.begin(); p != procVSblock.end(); p++) {
		std::cout << p->first << "\t";
		for (auto b = p->second.begin(); b != p->second.end(); b++)
			std::cout << std::setprecision(4) << b->second << "\t";
		std::cout << std::endl;
	}
	std::cout << "======================================================================\n";
}