#include "Policies.h"
#include <algorithm>
#include <iostream>

Policies::Policies(int maxEntries, std::chrono::seconds expiryDuration)
    : max(maxEntries), duration(expiryDuration) {}

std::deque<WebPage> Policies::limit(std::deque<WebPage>& history) {
    std::deque<WebPage> result(history);
    if (result.size() > max) {
        result.erase(result.begin(), result.end() - (result.size() - max));
    }
    return result;
}

void Policies::setmax(int maxEntries) {
    max = maxEntries;
}

int Policies::getmax() const {
    return max;
}

void Policies::setduration(std::chrono::seconds duration) {
    duration = duration;
}

std::chrono::seconds Policies::getduration() const {
    return duration;
}