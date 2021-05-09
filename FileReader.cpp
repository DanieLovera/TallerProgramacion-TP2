#include "FileReader.h"

FileReader::FileReader(const std::string &fileName) : file {fileName} { }

FileReader::FileReader(FileReader &&other) : file {std::move(other.file)} { }

FileReader::~FileReader() {
	closeIfOpen();
}

FileReader& FileReader::operator=(FileReader &&other) {
	if (this == &other) return *this;
	closeIfOpen();
	file = std::move(other.file);
	return *this;
}

bool FileReader::readLine(std::string &buffer) {
	return std::getline(file, buffer).eof(); 
}

bool FileReader::readWord(std::string &buffer) {
	return (file >> buffer).eof();
}

void FileReader::closeIfOpen() {
	if (file.is_open()) {
		file.close();
	}
}
