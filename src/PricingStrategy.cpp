#include "../include/PricingStrategy.h"
#include <iostream>

// DefaultPricing implementation
double DefaultPricing::calculateFare(double distance, double baseRate) const {
    return baseRate + (distance * 15.0); // Base + ₹15/km
}

void DefaultPricing::displayStrategyName() const {
    cout << "Default Pricing Strategy" << endl;
}

// SurgePricing implementation
double SurgePricing::calculateFare(double distance, double baseRate) const {
    return (baseRate + (distance * 15.0)) * surgeMultiplier;
}

void SurgePricing::displayStrategyName() const {
    cout << "Surge Pricing Strategy (Multiplier: " << surgeMultiplier << "x)" << endl;
}

// RatingBasedPricing implementation
double RatingBasedPricing::calculateFare(double distance, double baseRate) const {
    double fare = baseRate + (distance * 15.0);
    // Discount for high-rated customers
    if (customerRating >= 4.5) {
        fare *= 0.9; // 10% discount
    }
    return fare;
}

void RatingBasedPricing::displayStrategyName() const {
    cout << "Rating-Based Pricing Strategy" << endl;
}
