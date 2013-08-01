#include <complex>

/**
 * A function to compute a value with a random Gaussian distribution, mean 0, standard deviation 1.
 * Based on the Abramowitz and Stegun method; this is the code given in the comp.lang.c FAQ.
 * See <http://c-faq.com/lib/gaussian.html>.
 */
static double random_gaussian()
{
    static double U, V;
    static int phase = 0;
    double Z;
    
    if(phase == 0) {
        U = (rand() + 1.) / (RAND_MAX + 2.);
        V = rand() / (RAND_MAX + 1.);
        Z = sqrt(-2 * log(U)) * sin(2 * M_PI * V);
    } else
        Z = sqrt(-2 * log(U)) * cos(2 * M_PI * V);
    
    phase = 1 - phase;
    
    return Z;
}


/**
 * Gets a complex with the real and imaginary components calculated using a random Gaussian distribution.
 */
static std::complex<double> random_gaussian_complex()
{
    return std::complex<double>(random_gaussian(), random_gaussian());
}
