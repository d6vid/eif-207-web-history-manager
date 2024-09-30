#include "policy.h"
#include <algorithm>
#include <iostream>

Policy::Policy(int maxEntries, std::chrono::seconds expiryDuration)
    : max(maxEntries), duration(expiryDuration) {}

void Policy::limit(std::vector<std::string>& history) {
    if (history.size() > max) {
        history.erase(history.begin(), history.end() - max);
    }
}

void Policy::clean(std::vector<std::pair<std::string, std::chrono::system_clock::time_point>>& historyTimestamps) {
    auto now = std::chrono::system_clock::now();
    for (auto it = historyTimestamps.begin(); it != historyTimestamps.end(); ) {
        if (now - it->second > duration) {
            it = historyTimestamps.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Policy::setmax(int maxEntries) {
    max = maxEntries;
}

int Policy::getmax() const {
    return max;
}

void Policy::setduration(std::chrono::seconds duration) {
    duration = duration;
}

std::chrono::seconds Policy::getduration() const {
    return duration;
}