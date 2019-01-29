#include "esphome/defines.h"

#ifdef USE_TEMPLATE_BINARY_SENSOR

#include "esphome/binary_sensor/template_binary_sensor.h"
#include "esphome/log.h"

ESPHOME_NAMESPACE_BEGIN

namespace binary_sensor {

static const char *TAG = "binary_sensor.template";

TemplateBinarySensor::TemplateBinarySensor(const std::string &name)
    : BinarySensor(name) {

}
void TemplateBinarySensor::loop() {
  auto s = this->f_();
  if (s.has_value()) {
    bool new_state = *s;
    if (this->is_first_state_ || this->last_state_ != new_state) {
      this->is_first_state_ = false;
      this->last_state_ = new_state;
      this->publish_state(new_state);
    }
  }
}
float TemplateBinarySensor::get_setup_priority() const {
  return setup_priority::HARDWARE;
}
void TemplateBinarySensor::set_template(std::function<optional<bool>()> &&f) {
  this->f_ = std::move(f);
}
void TemplateBinarySensor::dump_config() {
  LOG_BINARY_SENSOR("", "Template Binary Sensor", this);
}

} // namespace binary_sensor

ESPHOME_NAMESPACE_END

#endif //USE_TEMPLATE_BINARY_SENSOR

