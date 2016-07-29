#include <yarp/os/RFModule.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/INavigation2D.h>
#include <yarp/os/Time.h>
#include <yarp/os/LogStream.h>
#define PERIOD  0
#define TIMEOUT 60

typedef struct navigationTestFrame
{
    navigationTestFrame(){x = 0; y = 0; t = 0;};
    navigationTestFrame(double ix, double iy, double it)
    {
        x = ix;
        y = iy;
        t = it;
    }

    double x;
    double y;
    double t;
}navFrame;

typedef struct navigationTestStep
{
    navigationTestStep()
    {
        label = "unamed";
    }

    std::vector<navFrame>    frames;
    yarp::os::ConstString    label;
    navFrame                 absPos;

}navStep;

class NavTestModule : public yarp::os::RFModule
{
private:
    bool                       locationsStored;
    double                     period;
    yarp::dev::INavigation2D*  iNav;
    yarp::dev::PolyDriver      ddNavClient;
    std::vector<navStep>       stepVector;
    unsigned int               currentGoal;
    bool                       checkCurrentGoalReached();

    bool executeStep(navStep s);
public:
                    NavTestModule();
                    ~NavTestModule();
    virtual bool    configure(yarp::os::ResourceFinder& rf );
    virtual bool    close();
    virtual double  getPeriod();
    virtual bool    updateModule();
    virtual bool    interruptModule();
};
