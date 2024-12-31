#ifndef HOLT_WINTERS_FILTER_H
#define HOLT_WINTERS_FILTER_H

#include <Arduino.h>

// ChatGPT Generated
class HoltWintersFilter {
   private:
    float alpha;       // Smoothing factor for the level
    float beta;        // Smoothing factor for the trend
    float level;       // Current level
    float trend;       // Current trend
    bool initialized;  // Flag to check if filter is initialized

   public:
    // Constructor with default alpha and beta values
    HoltWintersFilter(float alpha = 0.2, float beta = 0.1)
        : alpha(alpha), beta(beta), level(0), trend(0), initialized(false) {}

    // Compute the smoothed value
    float compute(float current_value) {
        if (!initialized) {
            // Initialize level and trend with the first input
            level = current_value;
            trend = 0;  // No trend initially
            initialized = true;
        } else {
            // Update level and trend based on the Holt-Winters equations
            float prev_level = level;  // Store the previous level for trend calculation
            level = alpha * current_value + (1 - alpha) * (level + trend);
            trend = beta * (level - prev_level) + (1 - beta) * trend;
        }
        // Return the smoothed value
        return level + trend;
    }
};

#endif  // !HOLT_WINTERS_FILTER_H
