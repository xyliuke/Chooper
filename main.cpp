#include <sstream>
#include <iomanip>
#include "player/image_player.h"
#include "ffmpeg/codec_util.h"
//将视频拆分成图片
//ffmpeg -i test.mp4 -r 30 -f image2 foo-%05d.jpeg
int main() {
//    auto list = std::make_shared<std::vector<std::string>>();
//    for (int i = 1; i < 932; ++i) {
//        std::stringstream ss;
//        ss << "../test/resource/image_group/foo-";
//        ss << std::setw(5) << std::setfill('0') << i;
//        ss << ".jpeg";
//        list->push_back(ss.str());
//    }
//
//    auto imagePlayer = new plan9::ImagePlayer();
//    imagePlayer->SetImageList(list);
//    imagePlayer->Play();
//    imagePlayer->Show();

    plan9::CodecUtil *codec = new plan9::CodecUtil();
}