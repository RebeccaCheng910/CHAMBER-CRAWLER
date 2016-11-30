void Controller::setPlayer(char c) {
  if (c == 'd') {
 41     pc = make_shared<Drow>;
 42   }
 43   else if (c == 'v') {
 44     pc = make_shared<Vampire>;
 45   }
 46   else if (c == 't') {
 47     pc = make_shared<Troll>;
 48   }
 49   else if (c == 'g') {
 50     pc = make_shared<Goblin>;
 51   }
 52   else if (c == 'h') {
 53     pc = make_shared<Hippie>;
 54   }
 55   else pc = make_shared<Shade>;
 56 }