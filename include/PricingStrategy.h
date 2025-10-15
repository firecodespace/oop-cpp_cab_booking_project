#ifndef PRICINGSTRATEGY_H
#define PRICINGSTRATEGY_H

// Abstract base class for polymorphism
class PricingStrategy {
public:
    virtual ~PricingStrategy() {}
    virtual double calculateFare(double distance, double baseRate) const = 0; // Pure virtual
    virtual void displayStrategyName() const = 0;
};

// Concrete strategy classes
class DefaultPricing : public PricingStrategy {
public:
    double calculateFare(double distance, double baseRate) const override;
    void displayStrategyName() const override;
};

class SurgePricing : public PricingStrategy {
private:
    double surgeMultiplier;
public:
    SurgePricing(double multiplier = 1.5) : surgeMultiplier(multiplier) {}
    double calculateFare(double distance, double baseRate) const override;
    void displayStrategyName() const override;
};

class RatingBasedPricing : public PricingStrategy {
private:
    double customerRating;
public:
    RatingBasedPricing(double rating) : customerRating(rating) {}
    double calculateFare(double distance, double baseRate) const override;
    void displayStrategyName() const override;
};

#endif
