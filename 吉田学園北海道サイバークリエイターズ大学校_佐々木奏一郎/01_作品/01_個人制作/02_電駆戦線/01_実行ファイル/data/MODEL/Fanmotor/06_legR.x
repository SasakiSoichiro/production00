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
 8;
 2.49378;-10.41579;3.03490;,
 2.48288;-10.41346;-2.29629;,
 2.50608;-0.07115;-2.29181;,
 2.51697;-0.07348;3.03938;,
 -2.82511;-0.05920;-2.28088;,
 -2.81422;-0.06153;3.05033;,
 -2.84830;-10.40151;-2.28537;,
 -2.83741;-10.40385;3.04585;;
 
 6;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,1,0;,
 4;1,6,4,2;,
 4;7,0,3,5;;
 
 MeshMaterialList {
  7;
  6;
  6,
  6,
  6,
  6,
  6,
  6;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.019200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.434000;0.010416;0.000000;;
  }
  Material {
   0.380000;0.558400;0.558400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.143925;0.211494;0.211494;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.037600;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.021573;0.000000;0.459000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.671200;0.153600;0.169600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.171995;0.039360;0.043460;;
  }
 }
 MeshNormals {
  17;
  0.999995;-0.002242;-0.002045;,
  0.999995;-0.002242;-0.002045;,
  0.999995;-0.002242;-0.002045;,
  0.002242;0.999997;0.000434;,
  0.002242;0.999997;0.000434;,
  0.002242;0.999997;0.000434;,
  -0.999995;0.002241;0.002044;,
  -0.999995;0.002241;0.002044;,
  -0.999995;0.002241;0.002044;,
  -0.999995;0.002241;0.002044;,
  -0.002242;-0.999997;-0.000433;,
  -0.002242;-0.999997;-0.000433;,
  -0.002242;-0.999997;-0.000433;,
  -0.002049;0.000438;-0.999998;,
  -0.002049;0.000438;-0.999998;,
  0.002053;-0.000438;0.999998;,
  0.002053;-0.000438;0.999998;;
  6;
  4;0,1,2,0;,
  4;3,3,4,5;,
  4;6,7,8,9;,
  4;10,10,11,12;,
  4;13,13,14,13;,
  4;15,16,15,16;;
 }
}
