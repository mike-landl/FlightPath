#include "Solver.hpp"
#include "Log.hpp"

namespace FlightData
{
    Solver::Solver()
    {
        recorder_.ReadFile("../../../data/2017-01-17_Graz-Gleichenberg.txt");
        Log::Info("Read flight data file with {} entries.", recorder_.GetData().size());
    }

    auto Solver::Run() -> void
    {
        
    }
}
