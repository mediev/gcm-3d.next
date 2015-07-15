#include "libgcm/Dispatcher.hpp"

using namespace gcm;

class DispatcherTest {
public:
	void test1(uint numberOfWorkers) {
		std::cout << "\ntest1: one body 9 \n";
		Task task;
		BodyProperties boProp;
		BlockProperties blProp;
		
		blProp.computationalCost = 1;
		blProp.id = 0;
		boProp.blocks.push_back(blProp);	
		boProp.computationalCost = 9;
		boProp.id = 0;
		task.bodies.push_back(boProp);
		
		Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
		if ( ! Dispatcher::getInstance().isLoadBalanced() )
			Dispatcher::getInstance().printProcVSblock();
		Dispatcher::destroyInstance();
	};
	void test2(uint numberOfWorkers) {
		std::cout << "\ntest2: two equal bodies 1:1 \n";
		Task task;
		BodyProperties boProp;
		BlockProperties blProp;
		
		blProp.computationalCost = 1;
		blProp.id = 30;
		boProp.blocks.push_back(blProp);	
		boProp.computationalCost = 1;
		boProp.id = 3;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 100;
		boProp.blocks.push_back(blProp);	
		boProp.computationalCost = 1;
		boProp.id = 10;
		task.bodies.push_back(boProp);

		Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
		if (!Dispatcher::getInstance().isLoadBalanced())
			Dispatcher::getInstance().printProcVSblock();
		Dispatcher::destroyInstance();
	};
	void test3(uint numberOfWorkers) {
		std::cout << "\ntest3: two bodies 1:10 \n";
		Task task;
		BodyProperties boProp;
		BlockProperties blProp;
		
		blProp.computationalCost = 1;
		blProp.id = 30;
		boProp.blocks.push_back(blProp);	
		boProp.computationalCost = 1;
		boProp.id = 3;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 100;
		boProp.blocks.push_back(blProp);	
		boProp.computationalCost = 10;
		boProp.id = 10;
		task.bodies.push_back(boProp);
		
		Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
		if (!Dispatcher::getInstance().isLoadBalanced())
			Dispatcher::getInstance().printProcVSblock();
		Dispatcher::destroyInstance();
	};
	void test4(uint numberOfWorkers) {
		std::cout << "\ntest4: four equal bodies 1:1:1:1 \n";
		Task task;
		BodyProperties boProp;
		BlockProperties blProp;
		
		blProp.computationalCost = 1;
		blProp.id = 0;
		boProp.blocks.push_back(blProp);		
		boProp.computationalCost = 1;
		boProp.id = 0;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 100;
		boProp.blocks.push_back(blProp);		
		boProp.computationalCost = 1;
		boProp.id = 10;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 1000;
		boProp.blocks.push_back(blProp);		
		boProp.computationalCost = 1;
		boProp.id = 100;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 10000;
		boProp.blocks.push_back(blProp);		
		boProp.computationalCost = 1;
		boProp.id = 1000;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
		if (!Dispatcher::getInstance().isLoadBalanced())
			Dispatcher::getInstance().printProcVSblock();
		Dispatcher::destroyInstance();
	};
	void test5(uint numberOfWorkers) {
		std::cout << "\ntest5: three bodies 1:2:3\n";
		Task task;
		BodyProperties boProp;
		BlockProperties blProp;
		
		blProp.computationalCost = 1;
		blProp.id = 0;
		boProp.blocks.push_back(blProp);		
		boProp.computationalCost = 1;
		boProp.id = 0;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 5;
		blProp.id = 10;
		boProp.blocks.push_back(blProp);
		boProp.computationalCost = 2;
		boProp.id = 1;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 20;
		boProp.blocks.push_back(blProp);
		boProp.computationalCost = 3;
		boProp.id = 2;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
		if (!Dispatcher::getInstance().isLoadBalanced())
			Dispatcher::getInstance().printProcVSblock();
		Dispatcher::destroyInstance();
	};
	void test6(uint numberOfWorkers) {
		std::cout << "\ntest6: three bodies 1:2:3 with two equal blocks 1:1\n";
		Task task;
		BodyProperties boProp;
		BlockProperties blProp;
		
		blProp.computationalCost = 100;
		blProp.id = 0;
		boProp.blocks.push_back(blProp);		
		blProp.computationalCost = 100;
		blProp.id = 1;
		boProp.blocks.push_back(blProp);
		boProp.computationalCost = 1;
		boProp.id = 0;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 5;
		blProp.id = 10;
		boProp.blocks.push_back(blProp);
		blProp.computationalCost = 5;
		blProp.id = 11;
		boProp.blocks.push_back(blProp);
		boProp.computationalCost = 2;
		boProp.id = 1;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 20;
		boProp.blocks.push_back(blProp);
		blProp.computationalCost = 1;
		blProp.id = 21;
		boProp.blocks.push_back(blProp);
		boProp.computationalCost = 3;
		boProp.id = 2;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
		if (!Dispatcher::getInstance().isLoadBalanced())
			Dispatcher::getInstance().printProcVSblock();
		Dispatcher::destroyInstance();
	};
	void test7(uint numberOfWorkers) {
		std::cout << "\ntest7: two bodies 1:2 with blocks: first with 2:3, second with 1:5 \n";
		Task task;
		BodyProperties boProp;
		BlockProperties blProp;
		
		blProp.computationalCost = 2;
		blProp.id = 0;
		boProp.blocks.push_back(blProp);	
		blProp.computationalCost = 3;
		blProp.id = 1;
		boProp.blocks.push_back(blProp);
		boProp.computationalCost = 1;
		boProp.id = 0;
		task.bodies.push_back(boProp);
		boProp.blocks.clear();
		
		blProp.computationalCost = 1;
		blProp.id = 10;
		boProp.blocks.push_back(blProp);	
		blProp.computationalCost = 5;
		blProp.id = 11;
		boProp.blocks.push_back(blProp);	
		boProp.computationalCost = 2;
		boProp.id = 1;
		task.bodies.push_back(boProp);
		
		Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
		if (!Dispatcher::getInstance().isLoadBalanced())
			Dispatcher::getInstance().printProcVSblock();
		Dispatcher::destroyInstance();
	};
	void tests(uint numberOfWorkers) {
		std::cout << "\n\nTests for " << numberOfWorkers << " numberOfWorkers\n";
		test1(numberOfWorkers);
		test2(numberOfWorkers);
		test3(numberOfWorkers);
		test4(numberOfWorkers);
		test5(numberOfWorkers);
		test6(numberOfWorkers);
		test7(numberOfWorkers);
	}
};

int main() {
	uint numberOfWorkers;
	DispatcherTest dispatcherTest;
	
	numberOfWorkers = 1;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 2;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 3;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 4;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 5;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 6;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 8;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 10;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 16;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 20;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 50;
	dispatcherTest.tests(numberOfWorkers);
	
	numberOfWorkers = 100;
	dispatcherTest.tests(numberOfWorkers);
	
	return 0;
}
