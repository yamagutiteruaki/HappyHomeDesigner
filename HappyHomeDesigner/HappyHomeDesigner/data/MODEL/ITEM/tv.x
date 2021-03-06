xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 56;
 -6.47091;9.28561;-0.24792;,
 6.47091;9.28561;-0.24792;,
 6.47091;8.63193;-0.24792;,
 -6.47091;8.63193;-0.24792;,
 -6.94828;1.51869;-0.24792;,
 -6.47091;1.51869;-0.24792;,
 -6.47091;1.12331;-0.24792;,
 -6.94828;1.12331;-0.24792;,
 6.47091;1.51869;-0.24792;,
 6.47091;1.12331;-0.24792;,
 6.94828;1.51869;-0.24792;,
 6.94828;1.12331;-0.24792;,
 6.94828;1.51869;0.06205;,
 6.47091;1.51869;0.06205;,
 6.47091;1.12331;0.06205;,
 6.94828;1.12331;0.06205;,
 -6.47091;1.51869;0.06205;,
 -6.47091;1.12331;0.06205;,
 -6.94828;1.51869;0.06205;,
 -6.94828;1.12331;0.06205;,
 6.47091;8.63193;-0.06711;,
 -6.47091;8.63193;-0.06711;,
 6.47091;1.51869;-0.06711;,
 -6.47091;1.51869;-0.06711;,
 -6.94828;9.28561;-0.24792;,
 6.94828;9.28561;-0.24792;,
 6.94828;9.28561;0.06205;,
 6.47091;9.28561;0.06205;,
 -6.47091;9.28561;0.06205;,
 -6.94828;9.28561;0.06205;,
 0.00000;0.11578;-3.11273;,
 2.60779;0.11578;-2.20103;,
 2.60779;0.03292;-2.20103;,
 0.00000;0.03292;-3.11273;,
 3.68797;0.11578;0.00000;,
 3.68797;0.03292;0.00000;,
 2.60779;0.11578;2.20103;,
 2.60779;0.03292;2.20103;,
 0.00000;0.11578;3.11273;,
 0.00000;0.03292;3.11273;,
 -2.60779;0.11578;2.20103;,
 -2.60779;0.03292;2.20103;,
 -3.68797;0.11578;0.00000;,
 -3.68797;0.03292;0.00000;,
 -2.60779;0.11578;-2.20103;,
 -2.60779;0.03292;-2.20103;,
 0.00000;0.11578;0.00000;,
 0.00000;0.03292;0.00000;,
 0.56136;4.17560;0.01575;,
 -0.02752;4.17560;0.61390;,
 -0.02752;0.08090;0.85796;,
 0.85890;0.08090;-0.04244;,
 -0.61639;4.17560;0.01575;,
 -0.91394;0.08090;-0.04244;,
 -0.02752;4.17560;0.21513;,
 -0.02752;0.08090;0.25770;;
 
 60;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,11,9;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;16,18,19,17;,
 4;20,21,3,2;,
 4;22,20,2,8;,
 4;23,22,8,5;,
 4;21,23,5,3;,
 4;21,20,22,23;,
 4;24,0,5,4;,
 4;1,25,10,8;,
 4;26,27,13,12;,
 4;27,28,16,13;,
 4;28,29,18,16;,
 4;11,10,12,15;,
 4;4,7,19,18;,
 4;0,24,29,28;,
 4;1,0,28,27;,
 4;25,1,27,26;,
 4;7,6,17,19;,
 4;6,9,14,17;,
 4;9,11,15,14;,
 4;10,25,26,12;,
 4;24,4,18,29;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,30,33,45;,
 3;46,31,30;,
 3;46,34,31;,
 3;46,36,34;,
 3;46,38,36;,
 3;46,40,38;,
 3;46,42,40;,
 3;46,44,42;,
 3;46,30,44;,
 3;47,33,32;,
 3;47,32,35;,
 3;47,35,37;,
 3;47,37,39;,
 3;47,39,41;,
 3;47,41,43;,
 3;47,43,45;,
 3;47,45,33;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,48,51,53;,
 3;54,49,48;,
 3;54,52,49;,
 3;54,48,52;,
 3;55,51,50;,
 3;55,50,53;,
 3;55,53,51;;
 
 MeshMaterialList {
  2;
  60;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.012800;0.012800;0.012800;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.341600;0.800000;0.690400;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.427000;1.000000;0.863000;;
  }
 }
 MeshNormals {
  19;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.663469;0.000000;-0.748204;,
  1.000000;0.000000;0.000000;,
  0.663469;0.000000;0.748204;,
  0.000000;0.000000;1.000000;,
  -0.663469;0.000000;0.748204;,
  -1.000000;0.000000;0.000000;,
  -0.663469;0.000000;-0.748204;,
  0.000000;-1.000000;-0.000000;,
  0.711990;0.041777;0.700946;,
  -0.711993;0.041778;0.700943;,
  0.000000;0.014210;-0.999899;;
  60;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,7,7,14;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;;
 }
}
