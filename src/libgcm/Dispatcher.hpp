#ifndef GCM_DISPATCHER_HPP
#define	GCM_DISPATCHER_HPP

#include <limits>

#include "libgcm/util/Singleton.hpp"
#include "libgcm/Launcher.hpp"
#include "libgcm/util/Math.hpp"

namespace gcm {
	struct Task;
	
	class Dispatcher : public Singleton<Dispatcher> {
		// A matrix indexed by workers id at strings and 
		// blocks id at columns. At cell (procId, blockId)
		// load from block with id = blockId on the worker
		// with id = procId is stored. 
		// The sum of the string procId is total load on proc with procId.
		// The sum of the column blockId is total computationalCost of 
		// block with blockId.
		std::map<int, std::map<uint, real>> procVSblock;
		
	public:
		void distributeProcessors(const Task &task, const uint numberOfWorkers);
		void getProportionsOfBlockDivision(const uint blockId, std::map<int, real> &proportions);
		
	private:
		void initializeProcVSblock(const Task &task, const uint numberOfWorkers);
		/*
		 * Correct division parts of the most shared block 
		 * of the most loaded worker in order to
		 * balance load among the workers of the block
		 *
		 *    -
		 *    |                      -     -
		 *  e |     -                |     |
		 *    |     |              e |     | c
		 *    -     | c    ==>       |     |
		 *    |     |                -     -
		 *  a |     -          (a-x) |     | (d+x)
		 *    |     | d              |     |
		 *    -     -                -     -
		 * 
		 * a - load on the maxLoaded proc by mostShared block
		 * e - load on the maxLoaded proc by other blocks
		 * d - average load on other procs of mostShared block by mostShared block
		 * c - average load on other procs of mostShared block by other blocks
		 * 
		 * @return 0 if algo is not efficient more, 1 if algo is efficient yet
		 */
		int correctMaxLoadedMostShared();
		/**
		 * Move load from the most loaded to the least loaded proc
		 * in order to balance load but don't over-share blocks among procs
		 * 
		 * @return 0 if algo is not efficient more, 1 if algo is efficient yet
         */
		int correctMaxLoadedMinLoaded();
		/**
         * @param id rank of minimally loaded processor
         * @param number amount of processors with this minimal load
         * @param minLoad value of minimal load
         */
		void findMinLoadedProcId(int &id, uint &number, real &minLoad);
		/**
         * @param id rank of maximally loaded processor
         * @param number amount of processors with this maximal load
         * @param minLoad value of maximal load
         */
		void findMaxLoadedProcId(int &id, uint &number, real &maxLoad);
	public:
		bool isLoadBalanced();
		void printProcVSblock();
	};
}

#endif	/* GCM_DISPATCHER_HPP */

