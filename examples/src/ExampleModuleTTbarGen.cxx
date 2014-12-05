#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/common/include/PrintingModules.h"

using namespace std;
using namespace uhh2;

/** \brief Example for calculating and accessing the TTbarGen interpretation
 * 
 */
class ExampleModuleTTbarGen: public AnalysisModule {
public:
    
    explicit ExampleModuleTTbarGen(Context & ctx);
    virtual bool process(Event & event) override;

private:
    std::unique_ptr<AnalysisModule> printer;
    std::unique_ptr<AnalysisModule> ttgenprod;
    Event::Handle<TTbarGen> h_ttbargen;
};


ExampleModuleTTbarGen::ExampleModuleTTbarGen(Context & ctx){
    printer.reset(new GenParticlesPrinter(ctx));
    ttgenprod.reset(new TTbarGenProducer(ctx, "ttbargen", false));
    h_ttbargen = ctx.get_handle<TTbarGen>("ttbargen");
}


bool ExampleModuleTTbarGen::process(Event & event) {
    printer->process(event);
    ttgenprod->process(event);
    const auto & ttbargen = event.get(h_ttbargen);
    
    cout << "Decay channel is " << int(ttbargen.DecayChannel()) << endl;
    return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ExampleModuleTTbarGen)
