#pragma once

#include <map>
//Assimp include files. These three are usually needed.
#include "assimp.h"
#include "aiPostProcess.h"
#include "aiScene.h"

#include "GL/glut.h"
#include "IL/il.h"

#include <vector>
using std::vector;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)
#define TRUE                1
#define FALSE               0

//Variabile contenente il numero di oggetti da importare nel gioco. La numerazione parte da 1: settare accuratamente
//tale valore per evitare crash.
#define NUMOBJ 2	

//VARIABILI
//Currently this is hardcoded
//static const std::string basepath = "./models/textures/"; //obj..
extern const std::string basepath; //per i file blend

//L'oggetto globale della scena di Assimp
extern vector<struct aiScene*> scene;
extern vector<GLuint> scene_list;

//Immagini/Texture
extern std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
extern GLuint* textureIds;							// pointer to texture Array

//METODI
void initializeScene();
void get_bounding_box_for_node(const struct aiNode* nd,
	int num,
	struct aiVector3D* min,
	struct aiVector3D* max,
	struct aiMatrix4x4* trafo
);
void get_bounding_box(int num, struct aiVector3D* min, struct aiVector3D* max);
void color4_to_float4(const struct aiColor4D *c, float f[4]);
void set_float4(float f[4], float a, float b, float c, float d);
void apply_material(const struct aiMaterial *mtl);
void Color4f(const struct aiColor4D *color);
void recursive_render(const struct aiScene *sc, const struct aiNode* nd, float scale);
int loadasset(const char* path);
int LoadGLTextures(const aiScene* scene);