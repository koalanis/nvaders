#ifndef SCENES_H
#define SCENES_H

#include <string>

using std::string;
struct Scenes {
  int maxSizeRows;
  int maxSizeCols;
  std::string menu;
  std::string lose;
  std::string win;
  std::string border;

  Scenes() {
    maxSizeCols = 28;
    maxSizeRows = 29;

    border = "#############################\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#                           #\n";
    border += "#############################\n";

    menu = "#############################\n";
    menu += "#                           #\n";
    menu += "#          Welcome          #\n";
    menu += "#                           #\n";
    menu += "#             to            #\n";
    menu += "#                           #\n";
    menu += "#          Nvaders          #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#     press 'p' to play     #\n";
    menu += "#     press 'q' to quit     #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#     coded by koalanis     #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#                           #\n";
    menu += "#############################\n";

    lose = "#############################\n";
    lose += "#                           #\n";
    lose += "#         You LOSE          #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#       Your Score ::       #\n";
    lose += "   %i \n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#   press  'p' to restart   #\n";
    lose += "#   press  'q' to quit      #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#     Github:: koalanis     #\n";
    lose += "#                           #\n";
    lose += "#                           #\n";
    lose += "#############################\n";

    win = "#############################\n";
    win += "#                           #\n";
    win += "#          You WIN          #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#   press   'p' to restart  #\n";
    win += "#   press   'q' to quit     #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#     Github:: koalanis     #\n";
    win += "#                           #\n";
    win += "#                           #\n";
    win += "#############################\n";
  }
};

#endif
