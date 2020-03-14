#include "stdafx.h"

bool isPathValid(std::wstring path) {
	std::wstring str0 = path.substr(1, 2);
	if (str0.find(L":\\") != std::wstring::npos ||
		str0.find(L".\\") != std::wstring::npos ||
		str0.find(L":/") != std::wstring::npos
		) {
		return true;
	}
	else {
		return false;
	}

}

int wmain(int argc, wchar_t* argv[]) {
	setlocale(LC_ALL, "");
	std::wstring inputExe(argv[0]);
	std::wstring outputExe;
	size_t headOfExe = 0;
	size_t headPos = 0;
	if (isPathValid(inputExe)) {
		headPos = inputExe.rfind(L"\\") + 1;
	}
	size_t tailPos = inputExe.rfind(L".");
	if (tailPos != std::wstring::npos) {
		tailPos = tailPos - 1;
	}
	else {
		tailPos = inputExe.length();
	}
	outputExe = inputExe.substr(headPos, tailPos - headPos + 1);
	std::wstring outPath(L"wsl.exe ");
	outPath.append(outputExe);

	for (int i = 1; i < argc; i++) {
		std::wstring tmp(argv[i]);
		std::wstring tmpBuilder(L" ");
		if (isPathValid(tmp)) {
			tmpBuilder.append(L"$(wslpath \'");
			tmpBuilder.append(tmp);
			tmpBuilder.append(L" \')");
		}
		else {
			tmpBuilder.append(tmp);
		}
		outPath.append(tmpBuilder);

	}
	printf("%ls", outPath.c_str());
	//return _wsystem(outPath.c_str());
}