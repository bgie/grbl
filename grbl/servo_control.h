/*
  servo_control.h - pen servo control methods
  Part of Grbl

  Copyright (c) 2021 Brecht Kuppens
  Copyright (c) 2017-2019 Bart Dring - https://github.com/bdring/Grbl_Pen_Servo
  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef servo_control_h
#define servo_control_h

#ifdef PEN_SERVO

void servo_init();
void update_pen_from_z();

#endif // ifdef PEN_SERVO

#endif
