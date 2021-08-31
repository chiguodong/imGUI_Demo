#pragma once
#ifndef SHADERJOINTER_H
#define SHADERJOINTER_H

#include <vector>
#include <set>
#include <string>
#include <map>

class shaderJointer
{
public:
	shaderJointer();
	~shaderJointer();
	void addMicroDefine(std::string input) { m_microDefines.insert(input); }
	void deleteMicroDefine(std::string input) { m_microDefines.erase(input); };
	void addHeader(std::string input) { m_Headers.insert(input); }
	void deleteHeader(std::string input) { m_Headers.erase(input); };

	std::string readHeaderFile(const std::string &headName);
	std::string readFile(const std::string &filePath, const std::string &fileName);
	void addHeaderIntoShader();
	void addMicroDefineIntoShader(); 
	void expressHeader();
	void jointShader();//final interface

	std::string getVert() { return m_vert; }
	std::string getFrag() { return m_frag; }


private:
	std::string m_frag;
	std::string m_vert;

	std::set<std::string> m_microDefines;
	std::set<std::string> m_Headers;
	std::string m_baseResourcePath{""};
	std::string m_defaultFrag{""};
	std::map<std::string, std::string> headerToDefineMap = 
	{ {"Anisotripic", "ANISOTROPIC"}, {"clearCoat", "CLEARCOAT"} };
};

#endif SHADERJOINTER_H