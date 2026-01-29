#include <iostream>
#include <string>
#include <cstdlib>

int main()
{
    std::string inputPath;
    std::cout << "動画ファイルパスを入力してください > ";
    std::getline(std::cin, inputPath);

    if (inputPath.empty()) {
        std::cerr << "パスが入力されていません\n";
        return 1;
    }

    // 入力時に " が付いていたら除去
    if (inputPath.size() >= 2 &&
        inputPath.front() == '"' &&
        inputPath.back() == '"')
    {
        inputPath = inputPath.substr(1, inputPath.size() - 2);
    }

    // 拡張子を .wav に変更
    std::string outputPath = inputPath;
    size_t dotPos = outputPath.find_last_of('.');
    if (dotPos == std::string::npos) {
        std::cerr << "拡張子が見つかりません\n";
        return 1;
    }
    outputPath = outputPath.substr(0, dotPos) + ".wav";

    // ffmpeg コマンド
    std::string cmd =
        "ffmpeg -y -i \"" +
        inputPath +
        "\" -vn -acodec pcm_s16le -ar 44100 -ac 2 \"" +
        outputPath + "\"";

    std::cout << cmd << std::endl; 

    int ret = system(cmd.c_str());

    if (ret != 0) {
        std::cerr << "ffmpeg 実行エラー\n";
        return 1;
    }

    std::cout << "変換完了:\n" << outputPath << std::endl;
    return 0;
}
