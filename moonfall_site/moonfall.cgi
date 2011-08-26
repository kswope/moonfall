#!/usr/bin/env moonfall

page_width = 1000
large_em = "1.2em"
medium_em = "1.1em"

side_margin = 20

nav_link_attrs = {
   float = "right",
   line_height = 40,
   margin_right = 5,
   font_size = medium_em,
   color = "white",
}

header_div_attrs = {
   float = "left",
   border = "solid 1px white",
   height = 30
}

logo_width = 300

header_top_widths = fill{
   total = page_width,
   borders_dummy = 4, -- dummy to make room for borders
   logo = logo_width,
   pushdown = false,
}

header_bottom_widths = fill{
   total = page_width,
   borders_dummy = 10, -- dummy to make room for borders
   logo = logo_width,
   spacer = 300,
   example = false,
   contact = false,
   list = false,
   download = false,
}
