#include <complex>
#include <random>
#include <point3.h>

#define GRAVITY 9.8 // Acceleration due to gravity (m/s^2).

typedef std::complex<float> complex;

/**
* A class that simulates ocean waves at a given time using Tessendorf's wave equations and the FFT method.
*
* The equations referenced by the documentation comments are those in "Simulating Ocean Waves", (c) 1999-2001 Jerry Tessendorf (SIGGRAPH Course Notes 2002).
*
* This class assumes the 3ds Max coordinate system, i.e. X- and Y-axes are in the horizontal plane and the Z-axis goes up and down.
*/
class tessendorf {
    std::tr1::mt19937 engine;
    std::tr1::normal_distribution<float> dist;

    float               omega_0;                    /* Dispersion-sub-naught; calculated using Tessendorf's equation (17). */
    int                 M;                          /* Resolution of grid along X-axis (16 <= M <= 2048; where M = 2^x for integer x). */
    int                 N;                          /* Resolution of grid Y-axis (16 <= N <= 2048; where N = 2^y for integer y). */
    float               Lx;                         /* "Real-life" length of plane along X-axis (in m). */
    float               Ly;                         /* "Real-life" length of plane along Y-axis (in m). */
    float               l;                          /* Size limit that waves must surpass to be rendered. */
    float               A;                          /* Controls height of Phillips spectrum. */
    float               V;                          /* Wind speed (in m/s). */
    Point3              w_hat;                      /* Direction of wind. */
    float               lambda;                     /* Choppiness factor. */
    float               t;                          /* Time (in s). */
    float               T;                          /* Time of one phase of simulation. */
    unsigned long       seed;                       /* Seed for the pseudorandom number generator. */

    Point3*             vertices;
    complex*            h_tildes_in;
    complex*            disp_x_in;
    complex*            disp_y_in;
    complex*            h_tildes_out;
    complex*            disp_x_out;
    complex*            disp_y_out;

    // Values precached on initialization.
    float               P_h__L;                     /* Precached for tessendorf::P_h. Largest possible waves arising from a continuous wind of speed V. */
    float               P_h__l_2;                   /* Precached for tessendorf::P_h. Square of l (l being the wave size limit). */

public:
    /**
    * Creates a new Tessendorf wave simulation at a specified time, given the specified parameters.
    * \param amplitude controls height of Phillips spectrum
    * \param speed wind speed (in m/s)
    * \param direction direction of wind
    * \param choppiness choppiness factor; greater is choppier
    * \param time time (in s)
    * \param phaseDuration duration of one phase (in s)
    * \param resX resolution of grid along X-axis (16 <= M <= 2048; where M = 2^x for integer x)
    * \param resY resolution of grid along Y-axis (16 <= N <= 2048; where N = 2^y for integer y)
    * \param scaleX length of plane along X-axis (in m)
    * \param scaleY length of plane along Y-axis (in m)
    * \param waveSizeLimit size limit that waves must surpass to be rendered
    * \param rngSeed seed for the pseudorandom number generator
    */
    tessendorf(float amplitude, float speed, Point3 direction, float choppiness, float time, float phaseDuration, int resX, int resY, float scaleX, float scaleY, float waveSizeLimit, unsigned long rngSeed);
    
    ~tessendorf();

    /**
    * Generates the initial wave surface and performs Fast Fourier Transforms (FFTs) to calculate the displacement.
    * The main height displacement is based on the Fourier series in Tessendorf's equation (19).
    * The horizontal displacement is based on the Fourier series in equation (29).
    *
    * The configure() method must be called before calling simulate(). Otherwise, a NULL pointer will be returned.
    */
    Point3*             simulate();

private:
    /**
    * Gets the wave dispersion factor for a given vector k.
    * Calculated using Tessendorf's equations (14) and (18) combined.
    */
    float               omega(Point3 k);

    /**
    * Gets the value of the Phillips spectrum, which models wind-driven waves, for a given vector k.
    * Calculated using Tessendorf's equations (23) and (24) combined.
    */
    float               P_h(Point3 k);

    /**
    * Gets the value of h~-sub-naught for a given vector k at the current simulation time.
    * Calculated using Tessendorf's equation (25).
    */
    complex             h_tilde_0(Point3 k);

    /**
    * Gets the value of h~ for a given vector k at the current simulation time.
    * Calculated using Tessendorf's equation (26).
    */
    complex             h_tilde(Point3 k);
};
