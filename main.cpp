#include <iostream>
#include <fstream>
#include <string>

#define MAX_SIZE 10000

#define ERR_PARAM_PASSED -1
#define ERR_POLY_FACE -2
#define ERR_FILE_OPEN -3

//using namespace std;

// 1. Open the file7
// 2. Read the vectors, textures, and normals
// 3. Store all the values in temporary arrays
// 4. Reopen file
// 5. Find faces
// 6. Create outputs
//  a. If face has more than 4 vertices, print to the screen ERROR and exit

int main(int argc, char **argv)
{
    // Help Menu
    if(argv[1] != 0) {
        std::string arg1 = argv[1];
        std::string help1 = "/?";
        std::string help2 = "-help";
        if((arg1.compare(help1) == 0) || (arg1.compare(help2) == 0)){
            std::cout << "\nConvert an OBJ file to Javascript functions that can be used in WebGL. Outputs the data in a text file as four separate functions (vertices, indices, normals, and texture coordinates)." << std::endl;
            std::cout << "Parameter 1: The location of the OBJ file." << std::endl;
            std::cout << "Parameter 2: The directory to save the output file." << std::endl;
            std::cout << "Parameter 3: The name of the object you are creating. It's a good idea to capitalize the first letter." << std::endl;
            std::cout << "\nExample: \nobjToWebGL.exe C:\\3dObjects\\myObject.obj C:\\3dObjects\\myWebglFiles Cube" << std::endl;
            std::cout << "Creates a the file C:\\3dObjects\\myWebglFiles\\Cube.txt with code that can be copied and pasted into a WebGL project." << std::endl;
            std::cout << "\nNotes: \n-Does not work with n-gon faces (any face > 4 vertices). \n-Currently supports up to 10,000 vertices." << std::endl;

            return 0;
        }
    }

    if(argc < 4) {
        std::cout << "\nToo few parameters passed." << std::endl;
        std::cout << "objToWebGL.exe <.obj location> <write directory> <object name>" << std::endl;
        std::cout << "To read the help file, type '/?' or '-help' as the first parameter." << std::endl;
        return ERR_PARAM_PASSED;
    }
    else {
        std::cout << "Opening file to find components..." << std::endl;
    }

    int ret, i, retInt, retTemp, repeat, currElem, sign, numVert;
    int numVertices = 0;
    float retFloat;
    char retChar;
    std::string fileLine;
    std::string result;
    std::string inputFile = argv[1];
    std::string outputDir = argv[2];
    std::string objectName = argv[3];
    std::string outputFileName = outputDir + "\\" + objectName + ".txt";

    // Arrays
    float vertices[MAX_SIZE];   // Values collected directly from file
    int eVert = 0;
    float textures[MAX_SIZE];
    int eText = 0;
    float normals[MAX_SIZE];
    int eNorm = 0;

    // =================================================================
    // PART 1
    // =================================================================

    // Open the file passed as a parameter
    std::ifstream objFile (argv[1]);
    if(!objFile.is_open()) {
            std::cout << "Could not open file " << argv[1] << std::endl;
            return ERR_FILE_OPEN;
    }

    // Read file. Stop at EOF (== 0)
    while(std::getline(objFile, fileLine)){
        std::cout << fileLine << std::endl;

        // VERTICES
        if((fileLine[0] == 'v') && (fileLine[1] == ' ')){
            // If vertices found (v), store in vertices array
            i = 2;
            for(repeat=0; repeat<3; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                vertices[eVert] = (retInt + retFloat) * sign;
                std::cout << vertices[eVert] << std::endl;
                eVert++;

                i++;
            }
            numVertices++;

        }
        // TEXTURES
        else if((fileLine[0] == 'v') && (fileLine[1] == 't')){
            // If vertices found (v), store in vertices array
            i = 3;
            for(repeat=0; repeat<2; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                textures[eText] = (retInt + retFloat) * sign;
                std::cout << textures[eText] << std::endl;
                eText++;

                i++;
            }

        }
        // NORMALS
        else if((fileLine[0] == 'v') && (fileLine[1] == 'n')){
            // If vertices found (v), store in vertices array
            i = 3;
            for(repeat=0; repeat<3; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                normals[eNorm] = (retInt + retFloat) * sign;
                std::cout << normals[eNorm] << std::endl;
                eNorm++;

                i++;
            }

        }
    }

    // Close current file
    objFile.close();

    // Wait for file to close
    while(objFile.is_open()) continue;


    // =================================================================
    // PART 2
    // =================================================================
    int currIndi = 0;
    int currFaceElement = 0;
    int eFace, startElem;

    int faceVerts[5];    // Values indicating indices
    int eFaceVert = 0;
    int faceTexts[5];
    int eFaceText = 0;
    int faceNorms[5];
    int eFaceNorm = 0;

    float outputVerts[MAX_SIZE];     // The vertices selected by the face
    int eOutVert = 0;
    float outputTexts[MAX_SIZE];
    int eOutText = 0;
    float outputNorms[MAX_SIZE];
    int eOutNorm = 0;
    int outputIndis[MAX_SIZE];
    int eOutIndi = 0;

    int faceNumVert[MAX_SIZE];  // Faces have 3 or 4 vertices. This will show how many faces will need to be interpreted when writing to the file
    int eFaceNumVert = 0;


    // Open File
    // std::ifstream objFile (argv[1]);
    objFile.open(argv[1]);
    if(!objFile.is_open()) {
            std::cout << "Could not open file " << argv[1] << std::endl;
            return ERR_FILE_OPEN;
    }
    else {
        std::cout << "Opening file to find faces..." << std::endl;
    }

    // Find Faces
    while(std::getline(objFile, fileLine)){
        if((fileLine[0] == 'f') && (fileLine[1] == ' ')) {
            // The first number of each group is the vert
            i = 2;
            eFace = 0;
            numVert = 0;
            // Search for numbers until the end of the string is found
            while(fileLine[i] != 0) {
                // Check if more than 4 vertices for face
                if(numVert >= 4) {
                    std::cout << "ERROR: Too many vertices in face. Exiting without finishing." << std::endl;
                    return ERR_POLY_FACE;
                }

                // Vertex
                retInt = 0;
                retChar = '0';
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceVerts[eFace] = retInt;

                // Textures
                retInt = 0;
                retChar = '0';
                i++;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceTexts[eFace] = retInt;

                // Normals
                retInt = 0;
                retChar = '0';
                i++;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceNorms[eFace] = retInt;

                if(fileLine[i] == ' ') i++;

                numVert++;
                eFace++;
            }

            // Create elements for first face of read string
            // Each veftex contains 3 values, so 9 values are created for one triangle
            for(currFaceElement = 0; currFaceElement < 3; currFaceElement++) {
                // VERTICES: X, Y, Z for first triangle
                startElem = ( faceVerts[currFaceElement] - 1 ) * 3;
                outputVerts[eOutVert] = vertices[startElem];
                eOutVert++;
                outputVerts[eOutVert] = vertices[startElem + 1];
                eOutVert++;
                outputVerts[eOutVert] = vertices[startElem + 2];
                eOutVert++;

                // TEXTURES
                startElem = ( faceTexts[currFaceElement] - 1 ) * 2;
                outputTexts[eOutText] = textures[startElem];
                eOutText++;
                outputTexts[eOutText] = textures[startElem + 1];
                eOutText++;

                // NORMALS
                startElem = ( faceNorms[currFaceElement] - 1 ) * 3;
                outputNorms[eOutNorm] = normals[startElem];
                eOutNorm++;
                outputNorms[eOutNorm] = normals[startElem + 1];
                eOutNorm++;
                outputNorms[eOutNorm] = normals[startElem + 2];
                eOutNorm++;

                // Indices to reference vertices
                outputIndis[eOutIndi] = currIndi;
                eOutIndi++;
                currIndi++;
            }

            // If face is made of 4 vertices, create another triangle
            // Create one more vertex and three more indices
            if(numVert > 3) {
                // X, Y, Z for first triangle
                startElem = ( faceVerts[3] - 1 ) * 3;
                outputVerts[eOutVert] = vertices[startElem];
                eOutVert++;
                outputVerts[eOutVert] = vertices[startElem + 1];
                eOutVert++;
                outputVerts[eOutVert] = vertices[startElem + 2];
                eOutVert++;

                // TEXTURES
                startElem = ( faceTexts[3] - 1 ) * 2;
                outputTexts[eOutText] = textures[startElem];
                eOutText++;
                outputTexts[eOutText] = textures[startElem + 1];
                eOutText++;

                // NORMALS
                startElem = ( faceNorms[3] - 1 ) * 3;
                outputNorms[eOutNorm] = normals[startElem];
                eOutNorm++;
                outputNorms[eOutNorm] = normals[startElem + 1];
                eOutNorm++;
                outputNorms[eOutNorm] = normals[startElem + 2];
                eOutNorm++;

                // The three indices for the first triangle have been created.
                // Create the indices to form the triangle that includes this vertex.
                // This will be the new vertex value and the two previous indices
                outputIndis[eOutIndi] = outputIndis[eOutIndi - 1];
                eOutIndi++;
                outputIndis[eOutIndi] = currIndi;
                eOutIndi++;
                outputIndis[eOutIndi] = outputIndis[eOutIndi - 5];
                eOutIndi++;
                currIndi++;
            }
        }
    }

    // DEBUG: Print out contents for all arrays
    /*std::cout << "\nindices = [" << std::endl;
    for(i=0; i<eOutIndi; i+=3) {
            std::cout << "\t" << outputIndis[i] << ", " << outputIndis[i+1] << ", " << outputIndis[i+2] << "," << std::endl;
    }
    std::cout << "];" << std::endl;

    std::cout << "\nvertices = [" << std::endl;
    for(i=0; i<eOutVert; i+=3) {
            std::cout << "\t" << outputVerts[i] << ", " << outputVerts[i+1] << ", " << outputVerts[i+2] << "," << std::endl;
    }
    std::cout << "];" << std::endl;

    std::cout << "\ntextures = [" << std::endl;
    for(i=0; i<eOutText; i+=2) {
            std::cout << "\t" << outputTexts[i] << ", " << outputTexts[i+1] << ", " << std::endl;
    }
    std::cout << "];" << std::endl;

    std::cout << "\nnormals = [" << std::endl;
    for(i=0; i<eOutNorm; i+=3) {
            std::cout << "\t" << outputNorms[i] << ", " << outputNorms[i+1] << ", " << outputNorms[i+2] << "," << std::endl;
    }
    std::cout << "];" << std::endl; */

    // Close File
    objFile.close();


    // =================================================================
    // Part 3
    // =================================================================
    // Create New file
    std::ofstream outFile (outputFileName);
    if(!outFile.is_open()) {
            std::cout << "Could not create file " << outputFileName << std::endl;
            return -1;
    }

    //
    // Write indices to file
    //
    std::cout << "Writing indices to file." << std::endl;
    outFile << "function create" + objectName + "Indi() {\n\tconst indices = [" << std::endl;
    for(i = 0; i<eOutIndi; i+=3) {
        outFile << "\t\t" << outputIndis[i] << ", " << outputIndis[i+1] << ", " << outputIndis[i+2] << ","<< std::endl;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn indices;\n}\n" << std::endl;

    //
    // Write vertices to file
    //
    std::cout << "Writing vertices to file." << std::endl;
    outFile << "function create" + objectName + "Vert() {\n\tconst vertices = [" << std::endl;
    for(i=0; i<eOutVert; i+=3) {
        outFile << "\t\t" << outputVerts[i] << ", " << outputVerts[i+1] << ", " << outputVerts[i+2] << "," << std::endl;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn vertices;\n}\n" << std::endl;

    //
    // Write Textures to file
    //
    std::cout << "Writing texture coordinates to file." << std::endl;
    outFile << "function create" + objectName + "Text() {\n\tconst textures = [" << std::endl;
    for(i=0; i<eOutText; i+=2) {
        outFile << "\t\t" << outputTexts[i] << ", " << outputTexts[i+1] << "," << std::endl;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn textures;\n}\n" << std::endl;

    //
    // Write normals to file
    //
    std::cout << "Writing normals to file." << std::endl;
    outFile << "function create" + objectName + "Norm() {\n\tconst normals = [" << std::endl;
    for(i=0; i<eOutNorm; i+=3) {
        outFile << "\t\t" << outputNorms[i] << ", " << outputNorms[i+1] << ", " << outputNorms[i+2] << "," << std::endl;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn normals;\n}\n" << std::endl;

    // Close file
    outFile.close();


    return 0;
}

/*
int main(int argc, char **argv)
{
    if(argc < 3) {
        std::cout << "Too few parameters passed." << std::endl;
        return -1;
    }

    int ret, i, retInt, retTemp, repeat, currElem, sign, numVert;
    int numVertices = 0;
    float retFloat;
    char retChar;
    std::string fileLine;
    std::string result;

    // Arrays
    float vertices[MAX_SIZE];   // Values collected directly from file
    int eVert = 0;
    float textures[MAX_SIZE];
    int eText = 0;
    float normals[MAX_SIZE];
    int eNorm = 0;
    int faceVerts[MAX_SIZE];    // Values indicating indices
    int eFaceVert = 0;
    int faceTexts[MAX_SIZE];
    int eFaceText = 0;
    int faceNorms[MAX_SIZE];
    int eFaceNorm = 0;
    float output[MAX_SIZE];     // The vertices selected by the face
    int eOutput = 0;
    int faceNumVert[MAX_SIZE];  // Faces have 3 or 4 vertices. This will show how many faces will need to be interpreted when writing to the file
    int eFaceNumVert = 0;


    // Open the file passed as a parameter
    std::ifstream objFile (argv[1]);
    if(!objFile.is_open()) {
            std::cout << "Could not open file " << argv[1] << std::endl;
            return -1;
    }

    // Read file. Stop at EOF (== 0)
    while(std::getline(objFile, fileLine)){
        std::cout << fileLine << std::endl;

        // VERTICES
        if((fileLine[0] == 'v') && (fileLine[1] == ' ')){
            // If vertices found (v), store in vertices array
            i = 2;
            for(repeat=0; repeat<3; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                vertices[eVert] = (retInt + retFloat) * sign;
                std::cout << vertices[eVert] << std::endl;
                eVert++;

                i++;
            }
            numVertices++;

        }
        // TEXTURES
        else if((fileLine[0] == 'v') && (fileLine[1] == 't')){
            // If vertices found (v), store in vertices array
            i = 3;
            for(repeat=0; repeat<2; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                textures[eText] = (retInt + retFloat) * sign;
                std::cout << textures[eText] << std::endl;
                eText++;

                i++;
            }

        }
        // NORMALS
        else if((fileLine[0] == 'v') && (fileLine[1] == 'n')){
            // If vertices found (v), store in vertices array
            i = 3;
            for(repeat=0; repeat<3; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                normals[eNorm] = (retInt + retFloat) * sign;
                std::cout << normals[eNorm] << std::endl;
                eNorm++;

                i++;
            }

        }
        // If faces found (f), store in faceVer
        else if((fileLine[0] == 'f') && (fileLine[1] == ' ')) {
            // The first number of each group is the vert
            i = 2;
            numVert = 0;
            while(fileLine[i] != 0) {
                // Vertex
                retInt = 0;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceVerts[eFaceVert] = retInt;
                eFaceVert++;

                // Textures
                retInt = 0;
                i++;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceTexts[eFaceText] = retInt;
                eFaceText++;

                // Normals
                retInt = 0;
                i++;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceNorms[eFaceNorm] = retInt;
                eFaceNorm++;

                if(fileLine[i] == ' ') i++;

                numVert++;
            }
            faceNumVert[eFaceNumVert] = numVert;
            eFaceNumVert++;
            std::cout << "Num Verts in face: " << numVert << std::endl;
        }
    }

    // Close current file
    objFile.close();

    // Create output vertices
    // Each face is 4 points
    // Every texture is tied to a vertex
    // [f] a b c d -> abc + cda
    // For each texture, copy data from vertices[] in new output

    // Create output file
    std::ofstream outFile (argv[2]);
    if(!outFile.is_open()) {
            std::cout << "Could not create file " << argv[2] << std::endl;
            return -1;
    }


    //
    // Update vertices and faceVerts
    //
    // Iterate through every faceTexts element
    int ftCurrElem, ftCurrValue, ftElemMax, ftDiffValue;
    int fvCurrElem, fvCurrValue, fvElemMax, fvDiffValue;
    int diffElem, verticesPrevElem, verticesNewElem;
    for(ftCurrElem=0; ftCurrElem<eFaceText; ftCurrElem++) {
        // Record the current value of the faceTexts array
        ftCurrValue = faceTexts[ftCurrElem];
        // Record the current associated value for faceVerts
        fvCurrValue = faceVerts[ftCurrElem];
        // Search through remaining faceVerts value for fvCurrValue
        for(fvCurrElem=ftCurrElem+1; fvCurrElem<eFaceText; fvCurrElem++) {
            // If ==fvCurrValue but !=ftCurrValue -> Mismatched pair: Update the vertex
            if((faceVerts[fvCurrElem] == fvCurrValue) && (faceTexts[fvCurrElem] != ftCurrValue)) {
                // Mismatch found. Now we have to run through the remaining values (including this one)
                // looking for this exact pair and update the vertex value.
                ftDiffValue = faceTexts[fvCurrElem];
                fvDiffValue = ++numVertices;
                for(diffElem=fvCurrElem; diffElem<eFaceText; diffElem++) {
                    // If match found, update the vertex to fvDiffValue
                    // Here we are only changing faceVerts of the current pair
                    if((faceTexts[diffElem] == ftDiffValue) && (faceVerts[diffElem] == fvCurrValue)) {
                        faceVerts[diffElem] = fvDiffValue;
                    }
                }

                // Copy the actual vertex data in vertices
                verticesPrevElem = (fvCurrValue - 1) * 3;
                verticesNewElem = (fvDiffValue - 1) * 3;
                vertices[verticesNewElem] = vertices[verticesPrevElem];
                vertices[verticesNewElem+1] = vertices[verticesPrevElem+1];
                vertices[verticesNewElem+2] = vertices[verticesPrevElem+2];
                eVert+=3;
            }
        }
    }

    //
    // Write vertices to file
    //
    outFile << "function createVert() {\n\tconst vertices = [" << std::endl;
    int j;
    for(i=0; i<eVert; i+=3) {
        outFile << "\t\t" << vertices[i] << ", " << vertices[i+1] << ", " << vertices[i+2] << "," << std::endl;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn vertices;\n}\n" << std::endl;


    //
    // Write Textures to file
    //
    outFile << "function createText() {\n\tconst texVerts = [" << std::endl;
    int numPrinted = 0;
    int tIndex;
    for(j=1; j<=numVertices; j++) {
        // Iterate through faceVerts, looking for values in numerical order i.e. faceVerts[i]==j 1<=j<=eFaceVert
        for(i=0; i<eFaceVert; i++) {
            if(faceVerts[i] == j) {
                tIndex = (faceTexts[i] - 1) * 2;
                outFile << "\t\t" << textures[tIndex] << ", " << textures[tIndex+1] << "," << std::endl;
                break;
            }
        }
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn texVerts;\n}\n" << std::endl;


    //
    // Write indices to file
    //
    outFile << "function createIndi() {\n\tconst indices = [" << std::endl;
    j = 0;
    for(i=0; i<eFaceVert; ) {
        outFile << "\t\t" << faceVerts[i]-1 <<", "<< faceVerts[i+1]-1 <<", "<< faceVerts[i+2]-1 << ","<< std::endl;
        if(faceNumVert[j] == 4) {
            outFile << "\t\t" << faceVerts[i+2]-1 <<", "<< faceVerts[i+3]-1 <<", "<< faceVerts[i]-1 << ","<< std::endl;
            i += 4;
        } else {
            i += 3;
        }

        j++;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn indices;\n}\n" << std::endl;

    //
    // Write normals to file
    //


    // Close file
    outFile.close();

    return 0;
}
*/
