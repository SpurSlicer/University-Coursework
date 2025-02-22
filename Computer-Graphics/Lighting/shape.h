#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include <iostream>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.14159265/180))
#define Sin(x) (sin((x)*3.14159265/180))

typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;

typedef coordinate color;

class shape {
    protected:
        std::vector<coordinate*> coords;
        std::vector<coordinate*> alt_coords;
        std::vector<coordinate*> normals;
        std::vector<coordinate*> lines;
        std::vector<std::vector<color*>> colors;
        coordinate* sphericalCoord(double, double);
        // Light values
        bool light     =   true;  // Lighting
        int one       =   1;  // Unit value
        int distance  =   5;  // Light distance
        int inc       =  10;  // Ball increment
        int smooth    =   1;  // Smooth/Flat shading
        int local     =   0;  // Local Viewer Model
        int emission  =   0;  // Emission intensity (%)
        int ambient   =  10;  // Ambient intensity (%)
        int diffuse   =  50;  // Diffuse intensity (%)
        int specular  =   0;  // Specular intensity (%)
        int shininess =   0;  // Shininess (power of two)
        float shiny   =   1;  // Shininess (value)
        int zh        =  90;  // Light azimuth
        float ylight  =   0;  // Elevation of light
        const float WHITE[4] = {1, 1, 1, 1};
        const float BLACK[4] = {0, 0, 0, 1};
        const float YELLOW[4]   = {1.0,1.0,0.0,1.0};
        const float EMISSION[4] = {0.0,0.0,(float)0.01*emission,1.0};
        enum generic_lighting_state {
            PLUS_X = 0,
            MINUS_X = 1,
            PLUS_Y = 2,
            MINUS_Y = 3,
            PLUS_Z = 4,
            MINUS_Z = 5
        };
    public:
        void printCoords(void);
        void generateNormalByTriangle(std::vector<coordinate*>, int);
        void generateNormalBySquare(std::vector<coordinate*>, int, bool);
        void activateSmoothness();
        void deactivateSmoothness();
        void deactivateLighting();
        float getAmbient();
        float getDiffuse();
        float getSpecular();
        int getLocal();
        bool isLightingEnabled();
        void setLightingEnabled(bool);
        coordinate* getGenericNormal(generic_lighting_state);
        void updateZh(double);
        double getZh();
        //void translate(double, double, double);
};
#endif
