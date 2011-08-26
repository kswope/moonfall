-- Copyright 2007 Kevin Swope, All Rights Reserved

-- This file is part of Moonfall.

-- Moonfall is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation; either version 3 of the License, or
-- (at your option) any later version.
  
-- Moonfall is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.

-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.


function fill (args)

   local total = 0
   local w = {} -- with value
   local w_sum = 0
   local wo = {} -- without value

   if type(args.total) ~= "number" then
      error("missing total", 2)
   else
      total = args.total
      args.total = nil
   end

   for k,v in pairs(args)  do
      if v then
	 w[k] = v
	 w_sum = w_sum + v
      else
	 table.insert(wo, k)
      end      
   end

   -- if there are false entries then populate them by splitting the difference
   if table.maxn(wo) > 0 then

      -- see if we can get a difference between total and sum of values
      headroom = total - w_sum

      -- get share for each with out
      share = headroom/table.maxn(wo)

      -- add wo keys to original hash, with the share as value
      -- also round down so we don't have floats in css
      for k,v in ipairs(wo) do
	 args[v] = math.floor(share)
      end

   end  

   return args

end

