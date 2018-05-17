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
 39;
 -18.84039;25.69516;18.84039;,
 18.84039;25.69516;18.84039;,
 18.84039;38.46865;18.84039;,
 -18.84039;38.46865;18.84039;,
 18.84039;25.69516;0.00000;,
 18.84039;0.78786;0.00000;,
 18.84039;0.78786;-18.84039;,
 18.84039;25.69516;-18.84039;,
 46.24854;25.69516;18.84039;,
 46.24854;25.69516;0.00000;,
 18.84039;25.69516;18.84039;,
 46.24854;0.78786;0.00000;,
 46.24854;0.78786;18.84039;,
 18.84039;0.78786;18.84039;,
 -18.84039;0.78786;18.84039;,
 -18.84039;38.46865;-18.84039;,
 18.84039;38.46865;-18.84039;,
 18.84039;0.78786;-18.84039;,
 -18.84039;0.78786;-18.84039;,
 -18.84039;46.43890;0.25165;,
 18.84039;46.43890;0.25165;,
 18.84039;38.46865;-18.84039;,
 -18.84039;38.46865;-18.84039;,
 18.84039;46.43890;0.25165;,
 -18.84039;46.43890;0.25165;,
 -18.84039;38.46865;18.84039;,
 18.84039;38.46865;18.84039;,
 18.84039;46.43890;0.25165;,
 18.84039;38.46865;0.25165;,
 -18.84039;46.43890;0.25165;,
 -18.84039;38.46865;0.25165;,
 -18.84039;46.43890;0.25165;,
 18.84039;46.43890;0.25165;,
 18.84039;38.46865;-18.84039;,
 -18.84039;38.46865;-18.84039;,
 -18.84039;0.78786;-18.84039;,
 -18.84039;0.78786;18.84039;,
 -18.84039;0.78786;-18.84039;,
 18.84039;0.78786;-18.84039;;
 
 17;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,4,10;,
 4;11,12,13,5;,
 4;9,11,5,4;,
 4;9,8,12,11;,
 4;0,14,12,8;,
 4;15,16,17,18;,
 4;19,20,21,22;,
 4;23,24,25,26;,
 3;27,26,28;,
 3;29,30,25;,
 3;31,22,30;,
 3;32,28,21;,
 4;26,10,7,33;,
 4;34,35,36,25;,
 4;37,38,13,36;;
 
 MeshMaterialList {
  3;
  17;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  2,
  1;;
  Material {
   0.800000;0.025098;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.031373;0.000000;;
  }
  Material {
   0.800000;0.721569;0.448627;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.901961;0.560784;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  9;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.999988;0.004793;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.922815;-0.385243;,
  0.000000;0.919080;0.394072;;
  17;
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;5,5,7,7;,
  4;5,5,8,8;,
  3;1,1,1;,
  3;6,6,6;,
  3;6,6,6;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;3,3,3,3;;
 }
 MeshTextureCoords {
  39;
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.246660;,
  1.000000;0.493320;,
  0.000000;0.246660;,
  0.000000;0.493320;,
  0.000000;0.746660;,
  1.000000;0.746660;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
