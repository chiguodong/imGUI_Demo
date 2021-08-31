#include "shaderJointer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex> 
#include <windows.h>

shaderJointer::shaderJointer() {

	char buf[1000];
	GetCurrentDirectory(1000, buf); //得到当前工作路径
	m_baseResourcePath = std::string(buf) + "\\resource\\";

	for (int i = 0; i < m_baseResourcePath.length(); i++) {
		if (m_baseResourcePath[i] == '\\') {
			m_baseResourcePath[i] = '/';
		}
	}
	m_defaultFrag = readFile(m_baseResourcePath, "BRDF.frag");
	m_vert = readFile(m_baseResourcePath, "defaultBrdf.vert");
}

shaderJointer::~shaderJointer() {

}

std::string shaderJointer::readFile(const std::string &filePath, const std::string &fileName) {
	auto path = filePath;
	if (path[path.size() - 1] != '/') {
		path = path + '/';
	}
	path = path + fileName;

	std::ifstream File;
	File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string text;
	try {
		File.open(path);
		std::stringstream ShaderStream;

		ShaderStream << File.rdbuf();

		File.close();

		text = ShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADERJOINTER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return text;
}

std::string shaderJointer::readHeaderFile(const std::string &headName) {
	auto headerPath = m_baseResourcePath + "algorithm";
	return readFile(headerPath, headName);
}

void shaderJointer::addHeaderIntoShader() {
	for (auto e : m_Headers) {
		m_frag = "#include <" + e + ".comp> \n" + m_frag;
	}
}

void shaderJointer::addMicroDefineIntoShader() {
	for (auto e : m_microDefines) {
		m_frag = "#define " + e + "\n" + m_frag;
	}
}

void shaderJointer::expressHeader() {
	std::string ans = m_frag;
	std::smatch result;
	std::string pattern{ "#include <(.*)>" };
	std::regex re(pattern);
	std::string::const_iterator iterStart = m_frag.begin();
	std::string::const_iterator iterEnd = m_frag.end();
	std::string temp;
	while (regex_search(iterStart, iterEnd, result, re)) {
		temp = result[0];
		auto a = result.str(1);
		std::string patternSpecific{ "#include <" + a + ">" };
		std::regex re2(patternSpecific);
		std::string headerStr = readHeaderFile(a);
		ans = regex_replace(ans, re2, headerStr);
		iterStart = result[0].second;
	}
	m_frag = ans;
}

void shaderJointer::jointShader() {
	m_frag = m_defaultFrag;
	addHeaderIntoShader();
	addMicroDefineIntoShader();
	m_frag = "#include <data.comp> \n" + m_frag;
	expressHeader();
}