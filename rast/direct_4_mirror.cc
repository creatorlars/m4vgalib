#include "vga/rast/direct_4_mirror.h"

#include "vga/arena.h"
#include "vga/copy_words.h"
#include "vga/vga.h"
#include "vga/rast/unpack_direct_x4_rev.h"

namespace vga {
namespace rast {

Direct_4_Mirror::Direct_4_Mirror(Direct_4 const & rast, unsigned top_line)
  : _r(rast),
    _top_line(top_line) {}

__attribute__((section(".ramcode")))
Rasterizer::LineShape Direct_4_Mirror::rasterize(unsigned line_number, Pixel *target) {
  line_number -= _top_line;
  line_number /= 4;
  if (line_number >= get_height()) return { 0, 0 };
  line_number = get_height() - 1 - line_number;

  unsigned char const *src = get_fg_buffer() + get_width() * line_number;

  unpack_direct_x4_rev_impl(src, target, get_width());

  return { 0, get_width() * 4 };
}

}  // namespace rast
}  // namespace vga