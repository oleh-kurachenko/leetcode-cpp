#include <string>
#include <vector>

class Robot {
  public:
    Robot(int width, int height) : _x_size{width}, _y_size{height} {}

    void step(int num) {
        _on_start = false;

        _pos += num;
        _pos %= 2 * _x_size + 2 * _y_size - 4;
    }

    std::vector<int> getPos() {
        if (!_pos) {
            return {0, 0};
        }

        switch (const char direction = get_direction()) {
        case 'e':
            return {_pos, 0};
        case 'n':
            return {_x_size - 1, _pos - _x_size + 1};
        case 'w':
            return {_x_size - (_pos - _x_size - _y_size + 2) - 1, _y_size - 1};
        case 's':
            return {0, _y_size - (_pos - 2 * _x_size - _y_size + 3) - 1};
        default:;
        }
        return {};
    }

    std::string getDir() {
        switch (const char direction = get_direction()) {
        case 'e':
            return "East";
        case 'n':
            return "North";
        case 'w':
            return "West";
        case 's':
            return "South";
        default:;
        }
        return "";
    }

  private:
    [[nodiscard]] char get_direction() const {
        if (!_pos) {
            if (_on_start) {
                return 'e';
            }
            return 's';
        }

        if (_pos > _x_size * 2 + _y_size - 3) {
            return 's';
        }
        if (_pos > _x_size + _y_size - 2) {
            return 'w';
        }
        if (_pos > _x_size - 1) {
            return 'n';
        }
        return 'e';
    }

    const int _x_size;
    const int _y_size;

    int _pos{0};
    bool _on_start{true};
};
