#pragma once



enum class OptionType: char {
    Call,
    Put,
};


class Option {
    private:
        double S_;
        double K_;
        double T_;
        double r_;
        double sigma_;
        OptionType type_;
        double d1_;
        double d2_;
    
    public:
        Option(double, double, double, double, double, OptionType);

        double price() const;

        double delta() const;

        double gamma() const;

        double vega() const;

        double theta() const;

        double rho() const;

};