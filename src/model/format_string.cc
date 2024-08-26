#include "format_string.h"

using namespace s21;

std::string FormatString::Convert() {
  setlocale(LC_ALL, "en_US.UTF-8");
  size_t str_length = wide_str_.length();
  char buffer[str_length + 1];  ///< temporary buffer to store C-string
  memset(buffer, 0, (str_length + 1));
  char add_symbol[3] = {0};
  std::wstring temp_wstr;  ///< temporary wstring to store wchar to be converted
  size_t iter_move = 0;    ///< value to move iterator in the string
  std::wstring::iterator it = wide_str_.begin();
  while (it != wide_str_.end()) {
    if (*it == L'X') {
      strcat(buffer, "x");
    } else if (*it == L'÷') {
      strcat(buffer, "/");
    } else if (*it == L'×') {
      strcat(buffer, "*");
    } else if (*it == L'√') {
      strcat(buffer, "r");
    } else if (*it == L'l') {
      if (*(it + 1) == L'n') {
        strcat(buffer, "l");
        iter_move = 2;
      } else {
        strcat(buffer, "L");
        iter_move = 3;
      }

      /* convert wide char into standard char */
    } else {
      /* add 2 current symbols to the buffer to check if the element is a
       * trigonometry function */
      temp_wstr = (*it);

      /* add next symbol */
      temp_wstr += (*(it + 1));

      /* convert 2 symbols to C-string */
      std::wcstombs(add_symbol, temp_wstr.c_str(), 2);

      if (add_symbol[0] == 'a') {
        /* if the element is asin, acos or atan, add current char to the buffer
         * in upper register */
        buffer[strlen(buffer)] = (add_symbol[1] - 32);
        iter_move = 4;
        /* otherwise add current char to the buffer */
      } else if (add_symbol[0] == 's' || add_symbol[0] == 'c' ||
                 add_symbol[0] == 't') {
        buffer[strlen(buffer)] = (add_symbol[0]);
        iter_move = 3;
      } else {
        buffer[strlen(buffer)] = (add_symbol[0]);
        iter_move = 1;
      }
    }
    it += iter_move;
  }
  basic_str_ = buffer;
  return basic_str_;
}