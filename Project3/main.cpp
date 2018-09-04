//--------------------------------------------------------------------------//
//                                                                          //
//  Project Assignment 3 - Eren Limon - 0054129                             //
//                                                                          //
//--------------------------------------------------------------------------//

#include "Angel.h"
#include <vector>
#include <stdlib.h>

typedef vec4  color4;
typedef vec4  point4;

//--------------------------Global Variables--------------------------------

GLuint buffer, buffer2, buffer3, buffer4;

// cube variables
const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
point4 points[NumVertices];
color4 colors[NumVertices];
vec3 normalsForCube[NumVertices];

// sphere variables
int numOfVerticesForSphere;
int numOfTrianglesForSphere;
int numOfEdgesForSphere;
point4 *pointsForSphere; // to be drawn
color4 *colorsForSphere; // to be used while drawing
point4 *verticesForSphere;
color4 *vertexColorsForSphere;


// car variables
int numOfVerticesForCar;
int numOfTrianglesForCar;
int numOfEdgesForCar;
point4 *pointsForCar; // to be drawn
color4 *colorsForCar; // to be used while drawing
point4 *verticesForCar;
color4 *vertexColorsForCar;

// ShapeX variables
int numOfVerticesForShapeX;
int numOfTrianglesForShapeX;
int numOfEdgesForShapeX;
point4 *pointsForShapeX; // to be drawn
color4 *colorsForShapeX; // to be used while drawing
point4 *verticesForShapeX;
color4 *vertexColorsForShapeX;
vec3 *normalsForVerticesShapeX;
vec3 *normalsForPointsShapeX;
vec2 *textCoordsForVertices;
vec2 *textCoordsForPoints;
// Texture objects and storage for texture image
GLuint textures[1];
const int TextureWidthSize = 2048;
const int TextureHeightSize = 2048;
GLubyte image[TextureWidthSize][TextureHeightSize][3];
//int image[TextureWidthSize*TextureHeightSize*3];
bool textureFlag = true; //enable texture mapping
GLuint TextureFlag; // texture flag uniform location
bool modifiedFlag = false;
GLuint ModifiedPhongFlag;
bool gouraudFlag = false;

// some enumerated types to increase readability
enum{ black = 0, red = 1, yellow = 2, green = 3, blue = 4, magenta = 5, white = 6, cyan = 7, randomized = 8};
enum{ sphereOption = 0, carOption = 1, cubeOption = 2, shapeXOption = 3};
enum{ wireframe = 0, solid = 1};
enum{ backgroundWhite = 0 , backgroundBlack = 1, backgroundGray = 2};
enum{ gouraud = 1 , phong = 2, modifiedPhong = 3};
enum{ perspective = 1 , ortho = 2};

// default options
int colorOption = randomized;
int shape = cubeOption;
int drawingMode = solid;
int backgroundColor = backgroundWhite;
int projectionOption = perspective;

// these two variables are needed for normalization
point4 globalMinVertex(INT_MAX);
point4 globalMaxVertex(INT_MIN);

// these two variables are needed for normalization
point4 globalMinVertex2(INT_MAX);
point4 globalMaxVertex2(INT_MIN);

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };


GLfloat scaleFactor[3] = {1.0, 1.0, 1.0};

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;

mat4  model_view;

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5, -0.5, -0.5, 1.0 ),
    point4( -0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5, -0.5, -0.5, 1.0 )
};

// RGBA olors
/*
 color4 vertex_colors[8] = {
 color4( 0.0, 0.0, 0.0, 1.0 ),  // black
 color4( 1.0, 0.0, 0.0, 1.0 ),  // red
 color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
 color4( 0.0, 1.0, 0.0, 1.0 ),  // green
 color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
 color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
 color4( 1.0, 1.0, 1.0, 1.0 ),  // white
 color4( 0.0, 1.0, 1.0, 1.0 )   // cyan
 };
 */
//----------------------------------------------------------------------------







//--------------------------------Methods-------------------------------------

/*  tridSphere method properly fills the pointsForSphere and colorsForSphere
 arrays which are used to create trianglular surfaces in glDrawArray method.
 */

int Index2 = 0;

void
tridSphere(int a, int b,int c)
{
    //std::cout << "Point indexes: " << a << " " << b << " " << c << std::endl
    colorsForSphere[Index2] = vertexColorsForSphere[a];
    pointsForSphere[Index2] = verticesForSphere[a];
    //std::cout << colorsForSphere[Index2] << std::endl;
    Index2++;
    
    colorsForSphere[Index2] = vertexColorsForSphere[b];
    pointsForSphere[Index2] = verticesForSphere[b];
    //std::cout << colorsForSphere[Index2] << std::endl;
    Index2++;
    
    colorsForSphere[Index2] = vertexColorsForSphere[c];
    pointsForSphere[Index2] = verticesForSphere[c];
    //std::cout << colorsForSphere[Index2] << std::endl;
    Index2++;
}


//----------------------------------------------------------------------------


/*  tridCar method properly fills the pointsForCar and colorsForCar
 arrays which are used to create trianglular surfaces in glDrawArray method.
 */

int Index3 = 0;

void
tridCar(int a, int b,int c)
{
    //std::cout << "Point indexes: " << a << " " << b << " " << c << std::endl
    colorsForCar[Index3] = vertexColorsForCar[a];
    pointsForCar[Index3] = verticesForCar[a];
    //std::cout << colorsForCar[Index3] << std::endl;
    Index3++;
    
    colorsForCar[Index3] = vertexColorsForCar[b];
    pointsForCar[Index3] = verticesForCar[b];
    //std::cout << colorsForCar[Index3] << std::endl;
    Index3++;
    
    colorsForCar[Index3] = vertexColorsForCar[c];
    pointsForCar[Index3] = verticesForCar[c];
    //std::cout << colorsForCar[Index3] << std::endl;
    Index3++;
}

//----------------------------------------------------------------------------


/*  tridShapeX method properly fills the pointsForShapeX and colorsForShapeX
 arrays which are used to create trianglular surfaces in glDrawArray method.
 */

int Index4 = 0;

void
tridShapeX(int a, int b,int c)
{
    normalsForPointsShapeX[Index4] = normalsForVerticesShapeX[a];
    textCoordsForPoints[Index4] = textCoordsForVertices[a];
    pointsForShapeX[Index4] = verticesForShapeX[a];
    Index4++;
    //std::cout << textCoordsForPoints[a] << std::endl;
    
    normalsForPointsShapeX[Index4] = normalsForVerticesShapeX[b];
    textCoordsForPoints[Index4] = textCoordsForVertices[b];
    pointsForShapeX[Index4] = verticesForShapeX[b];
    Index4++;
    
    normalsForPointsShapeX[Index4] = normalsForVerticesShapeX[c];
    textCoordsForPoints[Index4] = textCoordsForVertices[c];
    pointsForShapeX[Index4] = verticesForShapeX[c];
    Index4++;
}

/*  quad method properly fills the points and colors
 arrays which are used to create quadrilateral surfaces in glDrawArray method.
 */

int Index = 0;

void
quad( int a, int b, int c, int d )
{
    // Initialize temporary vectors along the quad's edge to
    //   compute its face normal
    vec4 u = vertices[b] - vertices[a];
    vec4 v = vertices[c] - vertices[b];
    
    vec3 normal = normalize( cross(u, v) );
    
    normalsForCube[Index] = normal; points[Index] = vertices[a]; Index++;
    normalsForCube[Index] = normal; points[Index] = vertices[b]; Index++;
    normalsForCube[Index] = normal; points[Index] = vertices[c]; Index++;
    normalsForCube[Index] = normal; points[Index] = vertices[a]; Index++;
    normalsForCube[Index] = normal; points[Index] = vertices[c]; Index++;
    normalsForCube[Index] = normal; points[Index] = vertices[d]; Index++;
    
}

//----------------------------------------------------------------------------


/*  colorbude method generates 12 triangles: 36 vertices and 36 colors
 */

void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

//----------------------------------------------------------------------------


/*  changeColor method changes the color arrays of all objects when the related
 submenu is chosen.
 */

void changeColor(int colorOption){
    
    // changing the color of the car
    for(int i = 0; i < numOfTrianglesForCar*3; i++){
        if(colorOption == red){
            colorsForCar[i] = color4( 1.0, 0.0, 0.0, 1.0 );  // red;
        } else if(colorOption == black){
            colorsForCar[i] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
        } else if(colorOption == yellow){
            colorsForCar[i] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
        } else if(colorOption == green){
            colorsForCar[i] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
        } else if(colorOption == blue){
            colorsForCar[i] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
        } else if(colorOption == magenta){
            colorsForCar[i] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
        } else if(colorOption == white){
            colorsForCar[i] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
        } else if(colorOption == cyan){
            colorsForCar[i] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan
        } else {
            colorsForCar[i] = color4(
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 );  // randomized
            
        }
        
    }
    
    // changing the color of the shapeX
    for(int i = 0; i < numOfTrianglesForShapeX*3; i++){
        if(colorOption == red){
            colorsForShapeX[i] = color4( 1.0, 0.0, 0.0, 1.0 );  // red;
        } else if(colorOption == black){
            colorsForShapeX[i] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
        } else if(colorOption == yellow){
            colorsForShapeX[i] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
        } else if(colorOption == green){
            colorsForShapeX[i] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
        } else if(colorOption == blue){
            colorsForShapeX[i] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
        } else if(colorOption == magenta){
            colorsForShapeX[i] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
        } else if(colorOption == white){
            colorsForShapeX[i] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
        } else if(colorOption == cyan){
            colorsForShapeX[i] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan
        } else {
            colorsForShapeX[i] = color4(
                                        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                        static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 );  // randomized
            
        }
        
    }
    
    
    // changing the color of the sphere
    for(int i = 0; i < numOfTrianglesForSphere*3; i++){
        if(colorOption == red){
            colorsForSphere[i] = color4( 1.0, 0.0, 0.0, 1.0 );  // red;
        } else if(colorOption == black){
            colorsForSphere[i] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
        } else if(colorOption == yellow){
            colorsForSphere[i] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
        } else if(colorOption == green){
            colorsForSphere[i] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
        } else if(colorOption == blue){
            colorsForSphere[i] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
        } else if(colorOption == magenta){
            colorsForSphere[i] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
        } else if(colorOption == white){
            colorsForSphere[i] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
        } else if(colorOption == cyan){
            colorsForSphere[i] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan
        } else {
            colorsForSphere[i] = color4(
                                        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                        static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 );  // randomized
            
        }
        
    }
    
    // changing the color of the cube
    for(int i = 0; i < NumVertices; i++){
        if(colorOption == red){
            colors[i] = color4( 1.0, 0.0, 0.0, 1.0 );  // red;
        } else if(colorOption == black){
            colors[i] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
        } else if(colorOption == yellow){
            colors[i] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
        } else if(colorOption == green){
            colors[i] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
        } else if(colorOption == blue){
            colors[i] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
        } else if(colorOption == magenta){
            colors[i] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
        } else if(colorOption == white){
            colors[i] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
        } else if(colorOption == cyan){
            colors[i] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan
        } else {
            colors[i] = color4(
                               static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                               static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                               static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 );  // randomized
            
        }
        
    }
    
}

//----------------------------------------------------------------------------


/*  readPPM */

bool
readPPM(char* name){
    
    std::string fileName(name);
    std::string path = "/Users/erenlimon/Desktop/MyApps/Project3/Project3/" + fileName;
    
    const char* pathAsPointer = path.c_str();
    
    
    int k, n, m, nm;
    char c;
    int i;
    char b[100];
    //float s;
    int red, green, blue;
    FILE * fd = fopen(pathAsPointer, "r"); // openning to read
    
    if( fd == NULL ){
        std::cout << "File cannot be opened!" << std::endl;
        return false;
    }
    
    fscanf(fd,"%[^\n] ",b);
    
    if(b[0]!='P' || b[1] != '3'){
        printf("%s is not a PPM file!\n", b);
        exit(0);
    }
    printf("%s is a PPM file\n",b);
    fscanf(fd, "%c",&c);
    while(c == '#') {
        fscanf(fd, "%[^\n] ", b);
        printf("%s\n",b);
        fscanf(fd, "%c",&c);
    }
    ungetc(c,fd);
    fscanf(fd, "%d %d %d", &n, &m, &k);
    printf("%d rows %d columns max value= %d\n",n,m,k);
    nm = n*m;
    //int *image = (int *)malloc(3*sizeof(GLuint)*nm);
    
     for(int i = 0; i < n; i++){
         for(int j = 0; j < m; j++){
                fscanf(fd,"%d %d %d",&red, &green, &blue );
                // n-i-1 because ppm's origin is bottom left
                image[n-i-1][j][0] = (GLubyte)red;
                image[n-i-1][j][1] = (GLubyte)green;
                image[n-i-1][j][2] = (GLubyte)blue;
         }
     }
     /*
    for(i=nm;i>0;i--){
        // this does not work
        //printf("%d\n",i);
        fscanf(fd,"%d %d %d",&red, &green, &blue );
        image[3*nm-3*i]=red;
        //image[3*nm-3*i][][0] = red;
        image[3*nm-3*i+1]=green;
        //image[3*nm-3*i][][1] = green;
        image[3*nm-3*i+2]=blue;
        //image[3*nm-3*i][][2] = blue;
    }*/
    
    fclose(fd);
    /*
     FILE * fd2 = fopen(pathAsPointer2, "w+");
     
     //36 da 1 new line
     for(i=0;i<nm*3;i++){
     int x = image[i];
     
     if(i % 34 == 0 && i != 0){
     fprintf(fd2, "\n");
     }
     
     fprintf(fd2, "%d ",x);
     
     
     }
     fclose(fd2);
     */
    return true;
}


//----------------------------------------------------------------------------


/*  readFromFile method reads from the off file given the file name, properly
 fills the array contents normalization is handled inside of this function.
 */

bool
fillNormalArray(char* name){
    //std::cout << "Name is: " << name;
    std::string fileName(name);
    std::string path = "/Users/erenlimon/Desktop/MyApps/Project3/Project3/" + fileName;
    
    const char* pathAsPointer = path.c_str();
    FILE * file = fopen(pathAsPointer, "r"); // openning to read
    if( file == NULL ){
        std::cout << "File cannot be opened!" << std::endl;
        return false;
    }
    
    int index = 0;
    int index2 = 0;
    int lineNumber = 1;
    
    
    
    while(true){
        
        if(lineNumber == 1){
            // skip the first line
            char firstWord[128];
            int line = fscanf(file, "%s", firstWord);
            if (line == EOF)
                break;
            if (strcmp(firstWord, "OFFX") == 0){
                //std::cout << "First word is: " << firstWord << "\n";
            }
            
        } else if(lineNumber == 2){
            // numOfVertices, numOfTriangles, numOfEdges
            fscanf(file, "%d %d %d\n", &numOfVerticesForShapeX, &numOfTrianglesForShapeX, &numOfEdgesForShapeX );
            
            //std::cout << numOfVerticesForShapeX << std::endl;
            // initialize arrays according to their given lengths in the files.
            verticesForShapeX = new point4[numOfVerticesForShapeX];
            vertexColorsForShapeX = new color4[numOfVerticesForShapeX];
            pointsForShapeX = new point4[numOfTrianglesForShapeX*3];
            colorsForShapeX = new color4[numOfTrianglesForShapeX*3];
            normalsForVerticesShapeX = new vec3[numOfVerticesForShapeX];
            normalsForPointsShapeX = new vec3[numOfTrianglesForShapeX*3];
            textCoordsForVertices = new vec2[numOfVerticesForShapeX];
            textCoordsForPoints = new vec2[numOfVerticesForShapeX*3];
        } else if(lineNumber <= numOfVerticesForShapeX + 2){
            
            point4 vertex;
            int line = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            if (line == EOF)
                break;
            //std::cout << vertex.x << " "<< vertex.y << " "<< vertex.z << "\n";
            vertex.w = 1.0;
            //verticesForShapeX[index] = vertex;
            
            // initially randomized colors to see objects properly. random colors helps
            // us to have a shadow-like effects.
            
            //vertexColorsForShapeX[index] = color;
            
            
            
        } else if(lineNumber <= numOfVerticesForShapeX + numOfTrianglesForShapeX + 2){
            
            int dummy;
            int ind1;
            int ind2;
            int ind3;
            int line = fscanf(file, "%d %d %d %d\n", &dummy, &ind1, &ind2, &ind3);
            //std::cout << dummy << " "<< ind1 << " "<< ind2 << " "<< ind3 << "\n";
            if (line == EOF)
                break;
            //tridShapeX(ind1, ind2, ind3);
            
        } else if(lineNumber <= numOfVerticesForShapeX + numOfTrianglesForShapeX + 2 + numOfVerticesForShapeX){
            // texture array will be mapped
            char dummy[80];
            vec2 text_coor;
            //int ind3;
            int line = fscanf(file, "%s %f %f\n", dummy, &text_coor.x, &text_coor.y);
            textCoordsForVertices[index2] = text_coor;
            //if(index2 == 0){
            //    std::cout << dummy << " "<< textCoordsForVertices[index2].x << " "<< textCoordsForVertices[index2].y  << "\n";
            //}
            //std::cout << dummy << " "<< textCoordsForVertices[index2].x << " "<< textCoordsForVertices[index2].y  << "\n";
            index2++;
            if (line == EOF)
                break;
        } else if(lineNumber <= numOfVerticesForShapeX + numOfTrianglesForShapeX + 2 + numOfVerticesForShapeX + numOfVerticesForShapeX){
            // normalsForVerticesShapeX will be filled
            //std::cout << lineNumber << std::endl;
            vec3 normal;
            char dummy[10];
            int line = fscanf(file, "%s %f %f %f\n", dummy, &normal.x, &normal.y, &normal.z);
            if (line == EOF)
                break;
            
            
            //std::cout << "First wordddd is: " << dummy << "\n";
            // std::cout << "normal for that vertex is: " << normal << "\n";
            normalsForVerticesShapeX[index] = normal;
            //std::cout << normalsForVerticesShapeX[index] << std::endl;
            index++;
            
        } else {
            char firstWord[128];
            int line = fscanf(file, "%s", firstWord);
            if (line == EOF){
                std::cout << "bitise geldi with: "<< lineNumber << std::endl;
                break;
            }
            
        }
        
        lineNumber++;
    }
    
    
    
    fclose(file);
    return true;
}


bool
readFromFile(char* name){
    
    //std::cout << "Name is: " << name;
    std::string fileName(name);
    std::string path = "/Users/erenlimon/Desktop/MyApps/Project3/Project3/" + fileName;
    
    const char* pathAsPointer = path.c_str();
    FILE * file = fopen(pathAsPointer, "r"); // openning to read
    if( file == NULL ){
        std::cout << "File cannot be opened!" << std::endl;
        return false;
    }
    
    int index = 0;
    int lineNumber = 1;
    
    if(strcmp(name,"sphere.off") == 0){
        // if we are reading the sphere file
        while(true){
            
            if(lineNumber == 1){
                // skip the first line
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
                if (strcmp(firstWord, "OFF") == 0){
                    //std::cout << "First word is: " << firstWord << "\n";
                }
                
            } else if(lineNumber == 2){
                // numOfVertices, numOfTriangles, numOfEdges
                
                fscanf(file, "%d %d %d\n", &numOfVerticesForSphere, &numOfTrianglesForSphere, &numOfEdgesForSphere );
                
                // initialize arrays according to their given lengths in the files.
                verticesForSphere = new point4[numOfVerticesForSphere];
                vertexColorsForSphere = new color4[numOfVerticesForSphere];
                pointsForSphere = new point4[numOfTrianglesForSphere*3];
                colorsForSphere = new color4[numOfTrianglesForSphere*3];
                
                
            } else if(lineNumber <= numOfVerticesForSphere + 2){
                
                point4 vertex;
                int line = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                if (line == EOF)
                    break;
                //std::cout << vertex.x << " "<< vertex.y << " "<< vertex.z << "\n";
                vertex.w = 1.0;
                verticesForSphere[index] = vertex;
                
                // initially randomized colors to see objects properly. random colors helps
                // us to have a shadow-like effects.
                color4 color;
                color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.w = 1.0;
                vertexColorsForSphere[index] = color;
                
                index++;
                
            } else if(lineNumber <= numOfVerticesForSphere + numOfTrianglesForSphere + 2){
                
                int dummy;
                int ind1;
                int ind2;
                int ind3;
                int line = fscanf(file, "%d %d %d %d\n", &dummy, &ind1, &ind2, &ind3);
                //std::cout << dummy << " "<< ind1 << " "<< ind2 << " "<< ind3 << "\n";
                if (line == EOF)
                    break;
                tridSphere(ind1, ind2, ind3);
                
            } else {
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
            }
            
            lineNumber++;
        }
        
    } else if(strcmp(name,"car.off") == 0){
        // if we are reading the car file
        while(true){
            
            if(lineNumber == 1){
                // skip the first line
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
                if (strcmp(firstWord, "OFF") == 0){
                    //std::cout << "First word is: " << firstWord << "\n";
                }
                
            } else if(lineNumber == 2){
                // numOfVertices, numOfTriangles, numOfEdges
                
                fscanf(file, "%d %d %d\n", &numOfVerticesForCar, &numOfTrianglesForCar, &numOfEdgesForCar );
                
                //std::cout << numOfVerticesForCar << " "<< numOfTrianglesForCar << " "<< numOfEdgesForCar << "\n";
                
                // initialize arrays according to their given lengths in the files.
                verticesForCar = new point4[numOfVerticesForCar];
                vertexColorsForCar = new color4[numOfVerticesForCar];
                pointsForCar = new point4[numOfTrianglesForCar*3];
                colorsForCar = new color4[numOfTrianglesForCar*3];
                
            } else if(lineNumber <= numOfVerticesForCar + 2){
                
                point4 vertex;
                int line = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                if (line == EOF)
                    break;
                //std::cout << vertex.x << " "<< vertex.y << " "<< vertex.z << "\n";
                vertex.w = 1.0;
                verticesForCar[index] = vertex;
                
                // To normalize, we need to find the max values
                if(vertex.x > globalMaxVertex.x)
                    globalMaxVertex.x = vertex.x;
                if(vertex.x < globalMinVertex.x)
                    globalMinVertex.x = vertex.x;
                
                if(vertex.y > globalMaxVertex.y)
                    globalMaxVertex.y = vertex.y;
                if(vertex.y < globalMinVertex.y)
                    globalMinVertex.y = vertex.y;
                
                if(vertex.z > globalMaxVertex.z)
                    globalMaxVertex.z = vertex.z;
                if(vertex.z < globalMinVertex.z)
                    globalMinVertex.z = vertex.z;
                
                // initially randomized colors to see objects properly. random colors helps
                // us to have a shadow-like effects.
                color4 color;
                color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.w = 1.0;
                
                vertexColorsForCar[index] = color;
                //std::cout << vertexColorsForCar[index] << std::endl;
                index++;
                
            } else if(lineNumber <= numOfVerticesForCar + numOfTrianglesForCar + 2){
                
                if(lineNumber==numOfVerticesForCar + 3){
                    // normalize once
                    
                    for(int i = 0; i < numOfVerticesForCar; i++){
                        /*if(verticesForCar[i].x > 0){
                         verticesForCar[i].x = verticesForCar[i].x / globalMaxVertex.x;
                         } else {
                         verticesForCar[i].x = verticesForCar[i].x / -globalMinVertex.x;
                         }
                         
                         if(verticesForCar[i].y > 0){
                         verticesForCar[i].y = verticesForCar[i].y / globalMaxVertex.y;
                         } else {
                         verticesForCar[i].y = verticesForCar[i].y / -globalMinVertex.y;
                         }
                         
                         if(verticesForCar[i].z > 0){
                         verticesForCar[i].z = verticesForCar[i].z / globalMaxVertex.z;
                         }else {
                         verticesForCar[i].z = verticesForCar[i].z / -globalMinVertex.z;
                         }*/
                        
                        verticesForCar[i].x = verticesForCar[i].x / (globalMaxVertex.x - globalMinVertex.x);
                        verticesForCar[i].y = verticesForCar[i].y / (globalMaxVertex.y - globalMinVertex.y);
                        verticesForCar[i].z = verticesForCar[i].z / (globalMaxVertex.z - globalMinVertex.z);
                        //std::cout << verticesForCar[i].x << " "<< verticesForCar[i].y << " "<< verticesForCar[i].z << "\n";
                    }
                }
                
                int dummy;
                int ind1;
                int ind2;
                int ind3;
                int line = fscanf(file, "%d %d %d %d\n", &dummy, &ind1, &ind2, &ind3);
                //std::cout << dummy << " "<< ind1 << " "<< ind2 << " "<< ind3 << "\n";
                if (line == EOF)
                    break;
                
                tridCar(ind1, ind2, ind3);
                
            } else {
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
            }
            
            lineNumber++;
        }
        
    } else if(strcmp(name,"shapeX.offx") == 0){
        // if we are reading the shapeX file
        while(true){
            
            if(lineNumber == 1){
                // skip the first line
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
                if (strcmp(firstWord, "OFFX") == 0){
                    std::cout << "First word is: " << firstWord << "\n";
                }
                
            } else if(lineNumber == 2){
                // numOfVertices, numOfTriangles, numOfEdges
                
                fscanf(file, "%d %d %d\n", &numOfVerticesForShapeX, &numOfTrianglesForShapeX, &numOfEdgesForShapeX );
                
                // initialize arrays according to their given lengths in the files.
                verticesForShapeX = new point4[numOfVerticesForShapeX];
                vertexColorsForShapeX = new color4[numOfVerticesForShapeX];
                pointsForShapeX = new point4[numOfTrianglesForShapeX*3];
                colorsForShapeX = new color4[numOfTrianglesForShapeX*3];
                //normalsForVerticesShapeX = new vec3[numOfVerticesForShapeX];
                //normalsForPointsShapeX = new vec3[numOfTrianglesForShapeX*3];
                
            } else if(lineNumber <= numOfVerticesForShapeX + 2){
                
                point4 vertex;
                int line = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                if (line == EOF)
                    break;
                //std::cout << vertex.x << " "<< vertex.y << " "<< vertex.z << "\n";
                vertex.w = 1.0;
                verticesForShapeX[index] = vertex;
                
                // initially randomized colors to see objects properly. random colors helps
                // us to have a shadow-like effects.
                color4 color;
                color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.w = 1.0;
                vertexColorsForShapeX[index] = color;
                
                index++;
                if(lineNumber == numOfVerticesForShapeX + 2){
                    // to center the object
                    
                    point4 mean(0, 0, 0, 0);
                    
                    for (int i = 0; i < numOfVerticesForShapeX; i++) {
                        mean += verticesForShapeX[i];
                    }
                    
                    mean /= numOfVerticesForShapeX;
                    
                    mean[3] = 0;
                    
                    for (int i = 0; i < numOfVerticesForShapeX; i++) {
                        verticesForShapeX[i] -= mean;
                    }
                    
                }
                
            } else if(lineNumber <= numOfVerticesForShapeX + numOfTrianglesForShapeX + 2){
                
                int dummy;
                int ind1;
                int ind2;
                int ind3;
                int line = fscanf(file, "%d %d %d %d\n", &dummy, &ind1, &ind2, &ind3);
                //std::cout << dummy << " "<< ind1 << " "<< ind2 << " "<< ind3 << "\n";
                if (line == EOF)
                    break;
                tridShapeX(ind1, ind2, ind3);
                
            } else if(lineNumber <= numOfVerticesForShapeX + numOfTrianglesForShapeX + 2 + numOfVerticesForShapeX){
                // texture array will be mapped
                int dummy;
                int ind1;
                int ind2;
                //int ind3;
                int line = fscanf(file, "%s %f %f\n", &dummy, &ind1, &ind2);
                //std::cout << dummy << " "<< ind1 << " "<< ind2 << " "<< ind3 << "\n";
                if (line == EOF)
                    break;
            } else if(lineNumber <= numOfVerticesForShapeX + numOfTrianglesForShapeX + 2 + numOfVerticesForShapeX + numOfVerticesForShapeX){
                
            } else {
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
            }
            
            lineNumber++;
        }
        
    } else {
        // other name options can be added later.
    }
    fclose(file);
    
    return true;
}

//----------------------------------------------------------------------------


GLuint vaoArray[4];

bool isFirstLoad = true;
GLuint program;
GLuint vPosition;
//GLuint vColor;
GLuint vNormal;
GLuint vTexCoord;


// OpenGL initialization
void
init()
{
   
    
    if(isFirstLoad){
        colorcube();
        
        char* obj1 = "sphere.off";
        char* obj2 = "car.off";
        char* obj3 = "shapeX.offx";
        char* obj4 = "texture.ppm";
        
        fillNormalArray(obj3);
        readFromFile(obj1);
        readFromFile(obj2);
        readFromFile(obj3);
        readPPM(obj4);
        
        
    }
    
    
    
    // Initialize texture objects
    glGenTextures( 2, textures );
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    
    /*gluBuild2DMipmaps(GL_TEXTURE_2D,
                      GL_RGB,
                      TextureWidthSize, TextureHeightSize,
                      GL_RGB,
                      GL_UNSIGNED_BYTE,
                      image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);*/
    
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, TextureWidthSize, TextureHeightSize, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR); //try here different alternatives
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //try here different alternatives
    
    
    
    if(gouraudFlag){
        program = InitShader( "vshader.glsl", "fshader.glsl" );
    } else {
        program = InitShader( "vshader_phong.glsl", "fshader_phong.glsl" );
    }
    
    
    
    // Create a vertex array object
    glGenVertexArrays( 4, vaoArray );
    glBindVertexArray( vaoArray[0] );
    
    
    // car methods
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForCar*3+ sizeof(color4)*numOfTrianglesForCar*3, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * numOfTrianglesForCar*3, pointsForCar );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForCar*3, sizeof(color4)*numOfTrianglesForCar*3, colorsForCar );
    vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    vNormal = glGetAttribLocation( program, "vNormal" );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForCar*3));
    /*
     vColor = glGetAttribLocation( program, "vColor" );
     glEnableVertexAttribArray( vColor );
     glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForCar*3) );
     */
    
    glBindVertexArray( vaoArray[1] );
    
    // sphere methods
    glGenBuffers( 1, &buffer2 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForSphere*3+ sizeof(color4)*numOfTrianglesForSphere*3, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * numOfTrianglesForSphere*3, pointsForSphere );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForSphere*3, sizeof(color4)*numOfTrianglesForSphere*3, colorsForSphere );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForSphere*3));
    /*glEnableVertexAttribArray( vColor );
     glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForSphere*3) );*/
    
    
    glBindVertexArray( vaoArray[2] );
    
    // cube methods
    glGenBuffers( 1, &buffer3 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer3 );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(normalsForCube), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(normalsForCube), normalsForCube );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );
    /*glEnableVertexAttribArray( vColor );
     glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );*/
    
    glBindVertexArray( vaoArray[3] );
    
    
    
    
    // shapeX methods
    
    glGenBuffers( 1, &buffer4 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer4 );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForShapeX*3+ sizeof(color4)*numOfTrianglesForShapeX*3 +
                 sizeof(vec2)*numOfTrianglesForShapeX*3 , NULL, GL_STATIC_DRAW );
    // Specify an offset to keep track of where we're placing data in our
    //   vertex array buffer.  We'll use the same technique when we
    //   associate the offsets with vertex attribute pointers.
    GLintptr offset = 0;
    glBufferSubData( GL_ARRAY_BUFFER, offset, sizeof(point4) * numOfTrianglesForShapeX*3, pointsForShapeX );
    offset += sizeof(point4) * numOfTrianglesForShapeX*3;
    glBufferSubData( GL_ARRAY_BUFFER, offset, sizeof(vec3)*numOfTrianglesForShapeX*3, normalsForPointsShapeX );
    offset += sizeof(vec3)*numOfTrianglesForShapeX*3;
    glBufferSubData( GL_ARRAY_BUFFER, offset, sizeof(vec2)*numOfTrianglesForShapeX*3, textCoordsForPoints );
    
    offset = 0;
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(offset) );
    offset += sizeof(point4) * numOfTrianglesForShapeX*3;
    
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset) );
    offset += sizeof(vec3)*numOfTrianglesForShapeX*3;
    
    vTexCoord = glGetAttribLocation( program, "vTexCoord" );
    glEnableVertexAttribArray( vTexCoord );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(offset) );
    
    TextureFlag = glGetUniformLocation(program, "TextureFlag");
    glUniform1i( TextureFlag, textureFlag );
    
    ModifiedPhongFlag = glGetUniformLocation(program, "ModifiedPhongFlag");
    glUniform1i( ModifiedPhongFlag, modifiedFlag );
    
    /*glEnableVertexAttribArray( vColor );
     glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForShapeX*3) );*/

    
    
    
    
    // Initialize shader lighting parameters
    point4 light_position( -1.0, 0.0, 0.0, 1.0 ); // point
    color4 light_ambient( 0.2, 0.2, 0.2, 1.0 ); // L_a
    color4 light_diffuse( 1.0, 1.0, 1.0, 1.0 ); // L_d
    color4 light_specular( 1.0, 1.0, 1.0, 1.0 ); // L_s
    
    color4 material_ambient( 1.0, 0.0, 1.0, 1.0 ); // k_a
    color4 material_diffuse( 1.0, 0.8, 0.0, 1.0 ); // k_d
    color4 material_specular( 1.0, 0.8, 0.0, 1.0 ); // k_s
    float  material_shininess = 100.0;
    
    
    // Initialize shader lighting parameters
    point4 light_position2( 1.0, 0.0, 0.0, 0.0 ); // directional
    
    
    color4 ambient_product = light_ambient * material_ambient; // k_a * L_a
    color4 diffuse_product = light_diffuse * material_diffuse; // k_d * L_d
    color4 specular_product = light_specular * material_specular; // k_s * L_s
    glUniform4fv( glGetUniformLocation(program, "AmbientProduct"),
                 1, ambient_product );
    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct"),
                 1, diffuse_product );
    glUniform4fv( glGetUniformLocation(program, "SpecularProduct"),
                 1, specular_product );
    
    glUniform4fv( glGetUniformLocation(program, "LightPosition"),
                 1, light_position );
    
    glUniform4fv( glGetUniformLocation(program, "LightPosition2"),
                 1, light_position2 );
    
    glUniform1f( glGetUniformLocation(program, "Shininess"),
                material_shininess );
    
    
    
    
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    // Set current program object
    glUseProgram( program );
    
    
    model_view=identity();
    
    // Enable hiddden surface removal
    glEnable( GL_DEPTH_TEST );
    
    // Set state variable "clear color" to clear buffer with.
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    //glClearColor( 0.0, 0.0, 0.0, 1.0 );
    //glClearColor( 0.5, 0.5, 0.5, 1.0 );
    
    
    
    isFirstLoad = false;
}

//----------------------------------------------------------------------------


void reshape( int w, int h )
{
    /*
    glViewport( 0, 0, w, h );
     
     GLfloat aspect = GLfloat(w)/h;
     mat4  projection = Perspective( 45.0, aspect, 0.5, 6.0 );
     
     glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
      
      */
    
    
    
    
    
      
    glViewport( 0, 0, w, h );
    
    // Set projection matrix
    mat4  projection;
    
    if(projectionOption == 1){
        if (w <= h){
            //projection = Perspective( 45.0, (GLfloat) w / (GLfloat) h, 0.5, 6.0 );
            projection = Perspective( 45.0, (GLfloat) w / (GLfloat) h, 0.1, 100 );
        } else {
            //projection = Perspective( 45.0, (GLfloat) h / (GLfloat) w, 0.5, 6.0 );
            projection = Perspective( 45.0, (GLfloat) w / (GLfloat) h, 0.1, 100 );
        }
    } else {
        if (w <= h){
            projection = Ortho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w, 1.0 * (GLfloat) h / (GLfloat) w, -1.0, 1.0);
        } else  {
            projection = Ortho(-1.0* (GLfloat) w / (GLfloat) h, 1.0 * (GLfloat) w / (GLfloat) h, -1.0, 1.0, -1.0, 1.0);
        }
    }
    
    
    
    
    
    
    
    
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
}
//----------------------------------------------------------------------------


void
display( void )
{
    
    
    
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //  Generate tha model-view matrixn
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const vec3 viewer_pos( 0.0, 0.0, 3.0 );
    
    if(backgroundColor == backgroundWhite){
        glClearColor( 1.0, 1.0, 1.0, 1.0 );
    } else if(backgroundColor == backgroundBlack){
        glClearColor( 0.0, 0.0, 0.0, 1.0 );
    } else if(backgroundColor == backgroundGray){
        glClearColor( 0.5, 0.5, 0.5, 1.0 );
    }
    
    if(shape == carOption){
        glBindVertexArray( vaoArray[0] );
        if(projectionOption == 1){
            model_view = ( Translate( -viewer_pos ) * RotateX( Theta[Xaxis] ) *
                          RotateY( Theta[Yaxis] ) *
                          RotateZ( Theta[Zaxis] ) *Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) );
        } else {
            model_view = ( RotateX( Theta[Xaxis] ) *
                          RotateY( Theta[Yaxis] ) *
                          RotateZ( Theta[Zaxis] ) *Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) * Translate(vec3(0.0, -0.5, 0.0)));
        }
    } else if(shape == sphereOption){
        glBindVertexArray( vaoArray[1] );
        if(projectionOption == 1){
            model_view = (Translate( -viewer_pos ) * RotateX( Theta[Xaxis] ) *
                          RotateY( Theta[Yaxis] ) *
                          RotateZ( Theta[Zaxis] ) * Scale(scaleFactor[0]/2, scaleFactor[1]/2, scaleFactor[2]/2) );
        } else {
            model_view = (RotateX( Theta[Xaxis] ) *
                          RotateY( Theta[Yaxis] ) *
                          RotateZ( Theta[Zaxis] ) * Scale(scaleFactor[0]/2, scaleFactor[1]/2, scaleFactor[2]/2) );
        }
        
        
    } else if(shape == cubeOption) {
        glBindVertexArray( vaoArray[2] );
        if(projectionOption == 1){
            model_view = (Translate( -viewer_pos ) *
                          RotateX( Theta[Xaxis] ) *
                          RotateY( Theta[Yaxis] ) *
                          RotateZ( Theta[Zaxis] ) * Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) );
        } else {
            model_view = (RotateX( Theta[Xaxis] ) *
                          RotateY( Theta[Yaxis] ) *
                          RotateZ( Theta[Zaxis] ) * Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) );
        }
        
    } else {
        glBindVertexArray( vaoArray[3] );
        if(projectionOption == 1){
            model_view = ( Translate( -viewer_pos ) *
                          RotateX( Theta[Xaxis] ) *
                          RotateY( Theta[Yaxis] ) *
                          RotateZ( Theta[Zaxis] ) * Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) );
        } else {
            model_view = (RotateX( Theta[Xaxis] ) *
                         RotateY( Theta[Yaxis] ) *
                         RotateZ( Theta[Zaxis] ) * Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) );
        }
        
        
        //model_view = ( Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) );
    }
    
    //  Generate tha model-view matrix
    //const vec3 displacement( 0.0, 0.0, -6.0 );
    //const vec3 displacement( 0.0, 0.0, 0.0 );
    /*model_view = ( Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) * Translate( displacement ) *
     RotateX( Theta[Xaxis] ) *
     RotateY( Theta[Yaxis] ) *
     RotateZ( Theta[Zaxis] ) );*/
    
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
    
    
    
    if(shape == carOption && drawingMode == wireframe){
        glDrawArrays( GL_LINES, 0, numOfTrianglesForCar*3 );
    }else if(shape == shapeXOption && drawingMode == wireframe) {
        glDrawArrays( GL_LINES, 0, numOfTrianglesForShapeX*3 );
    } else if(shape == shapeXOption && drawingMode == solid) {
        glDrawArrays( GL_TRIANGLES, 0, numOfTrianglesForShapeX*3 );
    } else if(shape == sphereOption && drawingMode == wireframe) {
        glDrawArrays( GL_LINES, 0, numOfTrianglesForSphere*3 );
    } else if(shape == carOption && drawingMode == solid) {
        glDrawArrays( GL_TRIANGLES, 0, numOfTrianglesForCar*3 );
    } else if(shape == sphereOption && drawingMode == solid){
        glDrawArrays( GL_TRIANGLES, 0, numOfTrianglesForSphere*3 );
    } else if(shape == cubeOption && drawingMode == wireframe){
        glDrawArrays( GL_LINES, 0, NumVertices );
    } else {
        glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    }
    
    
    //glFlush();
    
    
    glutSwapBuffers();
    
}


//----------------------------------------------------------------------------
float acceleration = 0.015; // 0.05 max - 0.005 min

void
idle( void )
{
    
    /*
     scaleFactor[0] *= (1.00 + acceleration);
     scaleFactor[1] *= (1.00 + acceleration);
     scaleFactor[2] *= (1.00 + acceleration);
     if(scaleFactor[0] >= 1.95 || scaleFactor[1] >= 1.95 || scaleFactor[0] >= 1.95){
     scaleFactor[0] = 1.95; // sometimes scalefactor becomes slightly higher than 1.95, which creates a bug
     scaleFactor[1] = 1.95; // so we need to set it back to 1.95
     scaleFactor[2] = 1.95;
     acceleration = -acceleration;
     } else if (scaleFactor[0] <= 1.0 || scaleFactor[1] <= 1.0 || scaleFactor[0] <= 1.0) {
     scaleFactor[0] = 1.0;
     scaleFactor[1] = 1.0;
     scaleFactor[2] = 1.0;
     acceleration = -acceleration;
     }
     */
    
    /*
     Theta[Axis] += 2.0;
     
     if ( Theta[Axis] > 360.0 ) {
     Theta[Axis] -= 360.0;
     }
     */
    /*
     Theta[Axis] += 1.0;
     
     if ( Theta[Axis] > 360.0 ) {
     Theta[Axis] -= 360.0;
     }
    */
    glutPostRedisplay();
    
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key,int x, int y )
{
    if(key == 'Q' | key == 'q')
        exit(0);
    else if(key == 'H' | key == 'h'){
        std::cout << "------------------------------" << std::endl;
        std::cout << "------/// Need Help? \\\\\\------" << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << "\nKey\tFunction\n" << std::endl;
        std::cout << "Q\tExit the program" << std::endl;
        std::cout << "Arrows + F1 + F2\tRotate the object in 3 directions" << std::endl;
        std::cout << "z\tScale Up" << std::endl;
        std::cout << "Z\tScale Down" << std::endl;
        std::cout << "t\tTurn off/on lights and load texture" << std::endl;
        std::cout << "H\tHelp" << std::endl;
    } else if(key == 'z'){
        scaleFactor[0] *= 1.1;
        scaleFactor[1] *= 1.1;
        scaleFactor[2] *= 1.1;
    } else if(key == 'Z'){
        scaleFactor[0] *= 0.9;
        scaleFactor[1] *= 0.9;
        scaleFactor[2] *= 0.9;
        
    }else if(key == 'Z'){
        scaleFactor[0] *= 0.9;
        scaleFactor[1] *= 0.9;
        scaleFactor[2] *= 0.9;
        
    }else if(key == 't'){
        if (textureFlag == true) textureFlag = false;
        else textureFlag = true;
        glUniform1i( TextureFlag, textureFlag );
        
    }else if(key == 'r'){
        //flag2 = false;
        //init();
        
    }
    glutPostRedisplay();

    
}

//----------------------------------------------------------------------------

void
arrowInput( int key,int x, int y )
{
    if (key == GLUT_KEY_UP) {
        Theta[Xaxis] += 3.0;
        
        if (Theta[Xaxis] > 360.0){
            Theta[Xaxis] -= 360.0;
        }
        
        
        /*
         if(acceleration < 0.05 && acceleration > 0){
         acceleration += 0.005;
         } else if (acceleration > -0.05 && acceleration < 0){
         acceleration -= 0.005;
         }
         */
        //std::cout << "Acc: " << acceleration << std::endl;
        glutPostRedisplay();
    } else if (key == GLUT_KEY_DOWN) {
        Theta[Xaxis] -= 3.0;
        
        if (Theta[Xaxis] < -360.0){
            Theta[Xaxis] += 360.0;
        }
        /*
         if(acceleration > 0.005 && acceleration > 0){
         acceleration -= 0.005;
         } else if (acceleration < -0.005 && acceleration < 0){
         acceleration += 0.005;
         }
         */
        
        //std::cout << "Acc down: " << acceleration << std::endl;
        glutPostRedisplay();
    } else if (key == GLUT_KEY_LEFT){
        
        Theta[Yaxis] += 3.0;
        
        if (Theta[Yaxis] > 360.0){
            Theta[Yaxis] -= 360.0;
        }
        
    } else if(key == GLUT_KEY_RIGHT){
        Theta[Yaxis] -= 3.0;
        
        if (Theta[Yaxis] < -360.0){
            Theta[Yaxis] += 360.0;
        }
        
    } else if (key == GLUT_KEY_F1){
        
        Theta[Zaxis] += 3.0;
        
        if (Theta[Zaxis] > 360.0){
            Theta[Zaxis] -= 360.0;
        }
        
    } else if(key == GLUT_KEY_F2){
        Theta[Zaxis] -= 3.0;
        
        if (Theta[Zaxis] < -360.0){
            Theta[Zaxis] += 360.0;
        }
        
    }
    
    
}


//----------------------------------------------------------------------------

void objectTypeCallback(int id)
{
    switch(id) {
        case 1:
            shape=sphereOption;
            break;
        case 2:
            shape=carOption;
            break;
        case 3:
            shape=cubeOption;
            break;
        case 4:
            shape=shapeXOption;
            break;
    }
    glutPostRedisplay();
}
//----------------------------------------------------------------------------

void drawingModeCallback(int id)
{
    switch(id) {
        case 1:
            drawingMode = wireframe;
            break;
        case 2:
            drawingMode = solid;
            break;
    }
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void backgroundColorCallback(int id)
{
    switch(id) {
        case 1:
            backgroundColor = backgroundWhite;
            break;
        case 2:
            backgroundColor = backgroundBlack;
            break;
        case 3:
            backgroundColor = backgroundGray;
            break;
    }
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void projectionCallback(int id)
{
    switch(id) {
        case 1:
            projectionOption = perspective;
            break;
        case 2:
            projectionOption = ortho;
            break;
    }
    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glutPostRedisplay();
}

//----------------------------------------------------------------------------
void shadingCallback(int id)
{
    switch(id) {
        case 1:
            modifiedFlag = false;
            glUniform1i( ModifiedPhongFlag, modifiedFlag );
            gouraudFlag = true;
            init();
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case 2:
            modifiedFlag = false;
            gouraudFlag = false;
            glUniform1i( ModifiedPhongFlag, modifiedFlag );
            init();
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case 3: // to see this effect, please focus the light on the center of a surface of a cube and change between gouraud and this, you will see that they're different.
            modifiedFlag = true;
            gouraudFlag = false;
            init();
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            glUniform1i( ModifiedPhongFlag, modifiedFlag );
            break;
    }
    glutPostRedisplay();
}
//----------------------------------------------------------------------------




void colorCallback(int id)
{
    switch(id) {
        case 1:
            colorOption = red;
            break;
        case 2:
            colorOption = black;
            break;
        case 3:
            colorOption = yellow;
            break;
        case 4:
            colorOption = green;
            break;
        case 5:
            colorOption = blue;
            break;
        case 6:
            colorOption = magenta;
            break;
        case 7:
            colorOption = white;
            break;
        case 8:
            colorOption = cyan;
            break;
        case 9:
            colorOption = randomized;
            break;
    }
    changeColor(colorOption);
    init();
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    
    
    glutInit( &argc, argv );
    glutInitDisplayMode(  GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 500, 700 );
    glutCreateWindow( "Project 3 - elimon15" );
    
    init();
    
    int objectTypeSubMenu = glutCreateMenu(objectTypeCallback);
    glutAddMenuEntry("Sphere", 1);
    glutAddMenuEntry("Car", 2);
    glutAddMenuEntry("Cube", 3);
    glutAddMenuEntry("shapeX", 4);
    
    int drawingModeSubMenu = glutCreateMenu(drawingModeCallback);
    glutAddMenuEntry("Wireframe", 1);
    glutAddMenuEntry("Solid", 2);
    
    int colorSubMenu = glutCreateMenu(colorCallback);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Black", 2);
    glutAddMenuEntry("Yellow", 3);
    glutAddMenuEntry("Green", 4);
    glutAddMenuEntry("Blue", 5);
    glutAddMenuEntry("Magenta", 6);
    glutAddMenuEntry("White", 7);
    glutAddMenuEntry("Cyan", 8);
    glutAddMenuEntry("Random", 9);
    
    int backgroundColorSubMenu = glutCreateMenu(backgroundColorCallback);
    glutAddMenuEntry("White", 1);
    glutAddMenuEntry("Black", 2);
    glutAddMenuEntry("Gray", 3);
    
    int shadingSubMenu = glutCreateMenu(shadingCallback);
    glutAddMenuEntry("Gouraud", 1);
    glutAddMenuEntry("Phong", 2);
    glutAddMenuEntry("Modified Phong", 3);
    
    int projectionSubMenu = glutCreateMenu(projectionCallback);
    glutAddMenuEntry("Perspective", 1);
    glutAddMenuEntry("Ortho", 2);
    
    glutCreateMenu(NULL);
    glutAddSubMenu("Object Type", objectTypeSubMenu);
    glutAddSubMenu("Drawing Mode", drawingModeSubMenu);
    //glutAddSubMenu("Color", colorSubMenu);
    glutAddSubMenu("Background Color", backgroundColorSubMenu);
    glutAddSubMenu("Shading", shadingSubMenu);
    glutAddSubMenu("Projection", projectionSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
    glutDisplayFunc( display ); // set display callback function
    glutReshapeFunc( reshape );
    glutIdleFunc( idle );
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowInput);
    
    
    glutMainLoop();
    return 0;
    
}

