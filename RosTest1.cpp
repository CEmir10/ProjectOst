#include <eeros/core/Executor.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/TimeDomain.hpp>
#include <eeros/safety/SafetySystem.hpp>
#include <eeros/logger/Logger.hpp>
#include <eeros/logger/StreamLogWriter.hpp>
#include <eeros/control/ros/RosPublisherDoubleArray.hpp>
#include <eeros/control/ros/RosPublisherDouble.hpp>
#include <eeros/control/ros/RosPublisherSafetyLevel.hpp>
#include <eeros/control/ros/RosSubscriberDoubleArray.hpp>
#include <eeros/control/ros/RosSubscriberDouble.hpp>
#include <eeros/control/ros/RosSubscribemyMsg.hpp>
#include <eeros/control/ros/RosPublishmyMsg.hpp>
//#include <eeros/control/ros/RosSubscriberSignal.hpp>
#include <eeros/control/ros/RosPublisherSignal.hpp>
#include <eeros/task/Lambda.hpp>
#include <ros/ros.h>
#include <signal.h>


using namespace eeros;
using namespace eeros::task;
using namespace eeros::control;
using namespace eeros::safety;
using namespace eeros::math;
using namespace eeros::logger;
using namespace eeros::hal;

class MyControlSystem {
public:
	MyControlSystem(double dt):
		c1({2.4, 0, 4.443, 23.6, -11.2, 1.3, 0.003}),
		c2(0.5),
		//vectorOut("/test/vector"),
		//vectorIn("/rosNodeTalker/vector"),
		//doubleOut("/test/val"),
		slOut("/test/safetyLevel"),
		//doubleIn("/rosNodeTalker/val"),
        //name("cstmsg//infodata"),  
       // numout("cstmpubnum//infodata"), // node and topic
        //numin("cstmsubnum//infodata"),
        numpub("numpub//infodata"),
       // numsub("numsub//infodata"),
       // numpubad("numpubad//info"),
       // numsubad("numsubad//info"),
        //numout1("cstnum//infodata"),
        //cities("template1//infodata"),
       // vectorVan("vector/info"),
		timedomain("Main time domain", dt, true) 
	{
 		//vectorOut.getIn().connect(c1.getOut());
		//doubleOut.getIn().connect(c2.getOut());
       // numout.getIn().connect(c2.getOut());
        numpub.getIn().connect(c2.getOut());
        //numpubad.getIn().connect(c2.getOut());
       // vectorVan.getIn().connect(c2.getOut());
        //name.setName(@myMsgBlock@);
        //name.getOut*(.setName(@myMsgSignal@);
		timedomain.addBlock(c1);
		timedomain.addBlock(c2);
		//timedomain.addBlock(vectorOut);
		//timedomain.addBlock(doubleOut);
		//timedomain.addBlock(slOut);
		//timedomain.addBlock(vectorIn);
		//timedomain.addBlock(doubleIn);
       // timedomain.addBlock(numpubad);
        //timedomain.addBlock(numsubad);
        //timedomain.addBlock(name);  //name
        //timedomain.addBlock(numout);
        //timedomain.addBlock(numin);
        //timedomain.addBlock(numout1);
        //timedomain.addBlock(cities);
        timedomain.addBlock(numpub);
        //timedomain.addBlock(numsub);
        //timedomain.addBlock(vectorVan);



		eeros::Executor::instance().add(timedomain);
	}
	virtual ~MyControlSystem() { }
	
	typedef eeros::math::Matrix<7, 1, double> Vector7;
	Constant<Vector7> c1;
	Constant<> c2;
	//RosPublisherDoubleArray<Vector7> vectorOut;	
    //RosSubscriberDoubleArray<Vector7> vectorIn; //dodao                        */ I HAVE TO WRITE GENERAL BLOCK FOR ROSPUBLISHER AND ROSSUBSCRIBER
	//RosPublisherDouble doubleOut;	
	RosPublisherSafetyLevel slOut;
    //RosSubscriberDouble doubleIn;                                                                               //RosPublisher<SafetyLevel> slOut;
    //RosSubscribemyMsg name;
    //RosPublishmyMsg numout;
    //RosSubscribemyMsg numin;
    
    RosPublisherSignal<test_pub_sub::myMsg::Type ,double>numpub;
   // RosSubscriberSignal<test_pub_sub::myMsg::Type,double>numsub;
    
     
   // RosPublisherSignal<test_pub_sub::swissMsg::Type,double>numpubad;
    //RosSubscriberSignal<test_pub_sub::swissMsg::Type,double>numsubad; // NE RADI TREBA POPRAVLJAT
    
    
   // RosPublisherSignal<std_msgs::Float64MultiArray::Type,double>numpdarray;
    
    //RosSubscriberSignal<std_msgs::Float64MultiArray::Type,double>numsdarray;
    
    
    
    //GeneralClassSubscribe<test_pub_sub::myMsg::Type,double> numout1;
    
    //GeneralClassSubscribe<test_pub_sub::swissMsg::Type,double> cities;
    
    //GeneralClassPublish<double,Vector2>vectorOut1;
    
    //GeneralClassSubscribe<double,Vector2>vectorIn1;
    
    
    //RosSubscriberDoubleArray<Vector2> vectorIn;	
    //RosSubscribe<myMsg2, double> name;                                                       //RosSubscriberDoubleArray<Vector2> vectorIn;	
   // RosSubscribe<myMsg3, int, double> name;                                                       //RosSubscriberDoubleArray<Vector2> vectorIn;	
	
	TimeDomain timedomain;
};

class MySafetyProperties : public SafetyProperties {
public:
	MySafetyProperties(MyControlSystem& cs) : slOne("one"), slTwo("two"), se("change") {	
		addLevel(slOne);
		addLevel(slTwo);
		slOne.addEvent(se, slTwo, kPrivateEvent);
		slTwo.addEvent(se, slOne, kPublicEvent);
		setEntryLevel(slOne);
		
		slOne.setLevelAction([&](SafetyContext* privateContext) {
			cs.c1.setValue(cs.c1.getValue() + diff);
			cs.c2.setValue(cs.c2.getValue() - diff);
			if ((slOne.getNofActivations() % 10) == 0) {
				//log.info() << cs.doubleIn.getOut().getSignal();
				//log.info() << cs.vectorIn.getOut().getSignal();
                //log.info() << cs.numsub.getOut().getSignal();
                //log.info() << cs.numsubad.getOut().getSignal();
                
                //log.info() << cs.numin.getOut().getSignal();
			}
			if ((slOne.getNofActivations() % 50) == 0) {
				privateContext->triggerEvent(se);
			}
		});

		slTwo.setLevelAction([&](SafetyContext* privateContext) {
			cs.c1.setValue(cs.c1.getValue() - diff);
			cs.c2.setValue(cs.c2.getValue() + diff);
			if ((slTwo.getNofActivations() % 10) == 0) {
				//log.info() << cs.doubleIn.getOut().getSignal();
				//log.info() << cs.vectorIn.getOut().getSignal();
               // log.info() << cs.numsub.getOut().getSignal();
                //log.info() << cs.numsubad.getOut().getSignal();

			}
			if ((slTwo.getNofActivations() % 50) == 0) {
				privateContext->triggerEvent(se);
			}
		});

	}

	SafetyLevel slOne;
	SafetyLevel slTwo;
	SafetyEvent se;
	Logger log;
	double diff = 0.1;
};

void signalHandler(int signum) {
	Executor::stop();
}

int main(int argc, char **argv) {	
	double dt = 0.1;

	StreamLogWriter w(std::cout);
	Logger::setDefaultWriter(&w);
	Logger log;
	w.show();
 
	log.info() << "ROS Test1 started";

	rosTools::initNode("eerosNode");
	log.trace() << "ROS node initialized.";
		
	MyControlSystem controlSystem(dt);
	MySafetyProperties safetyProperties(controlSystem);
	SafetySystem safetySystem(safetyProperties, dt);
	controlSystem.slOut.setSafetySystem(safetySystem);
	
	Lambda l1 ([&] () { });
	Periodic periodic("per1", 1, l1);
	periodic.monitors.push_back([&](PeriodicCounter &pc, Logger &log){
		//.info() << "myMsg" << controlSystem.numsub.getOut().getSignal();
       // log.info() << "stdMsg" << controlSystem.numsubad.getOut().getSignal();

      //  log.info() << "myTemplate" << controlSystem.numout1.getOut().getSignal();
       // log.info() << "Swiss Template" << controlSystem.cities.getOut().getSignal();
        
	});
    
	signal(SIGINT, signalHandler);	
	auto &executor = Executor::instance(); //The executor is responsible to run various different time domains in separated threads of execution
	executor.setMainTask(safetySystem);
    executor.add(periodic);
	executor.run();
	
	log.info() << "ROS Test1 end";
	return 0;
}
