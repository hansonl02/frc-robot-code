#ifndef C2018_SUBSYSTEMS_CLIMBER_BATTER_BATTER_H_
#define C2018_SUBSYSTEMS_CLIMBER_BATTER_BATTER_H_

namespace c2018 {

namespace batter {

class Batter {
 public:
  Batter() = default;
  bool Update(bool put_down_batter, bool outputs_enabled);
};

}  // namespace batter

}  // namespace c2018

#endif  // C2018_SUBSYSTEMS_CLIMBER_BATTER_BATTER_H_

