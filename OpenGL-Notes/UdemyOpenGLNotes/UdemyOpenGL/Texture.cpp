#include "Texture.h"
#include <iostream>

Texture::Texture() {
	fileLocation = "";
	ResetValues();
}

Texture::Texture(const char* fileLoc) {
	fileLocation = fileLoc;
	ResetValues();
}

void Texture::LoadTexture() {
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

	if (!texData) {
		printf("Failed to find: %s\n", fileLocation);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //for zoom in zoom out
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData); //merkezi hafizadaki pixel bilgileri ekran karti hafizasina kopyalaniyor
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

void Texture::UseTexture() {
	glActiveTexture(GL_TEXTURE0); //this will allow you to bind multiple textures
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture() {
	glDeleteTextures(1, &textureID);
	 
}

void Texture::ResetValues() {
	textureID = 0;
	width = 0;
	height = 0; 
	bitDepth = 0;
}

Texture::~Texture() {
	ClearTexture();
}