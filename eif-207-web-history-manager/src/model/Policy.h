#include <string>
#include <chrono>
#include <vector>

class Policy {
public:
    Policy(int max, std::chrono::seconds duration);
    void limit(std::vector<std::string>& history);
    void clean(std::vector<std::pair<std::string, std::chrono::system_clock::time_point>>& historyTimestamps);
    void setmax(int maxEntries);
    int getmax() const;
    void setduration(std::chrono::seconds duration);
    std::chrono::seconds getduration() const;
private:
    int max;
    std::chrono::seconds duration;
};