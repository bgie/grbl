/*
  servo_control.c - pen servo control methods
  Part of Grbl
 
  Copyright (c) 2021 Brecht Kuppens
  Copyright (c) 2017-2019 Bart Dring - https://github.com/bdring/Grbl_Pen_Servo
  Copyright (c) 2012-2017 Sungeun K. Jeon for Gnea Research LLC
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
 
#include "grbl.h"      
 
#ifdef PEN_SERVO

#define SERVO_PWM_DDR         DDRB
#define SERVO_PWM_BIT         3    // Uno Digital Pin 11 
#define SERVO_TCCRA_REGISTER  TCCR2A
#define SERVO_TCCRB_REGISTER  TCCR2B
#define SERVO_OCR_REGISTER    OCR2A
#define SERVO_COMB_BIT        COM2A1
 
#define Z_VALUE_PEN_RANGE   (Z_VALUE_PEN_UP - Z_VALUE_PEN_DOWN)
#define PEN_SERVO_RANGE     (PEN_SERVO_UP - PEN_SERVO_DOWN)
#define PEN_SERVO_MIN       (min(PEN_SERVO_UP, PEN_SERVO_DOWN))
#define PEN_SERVO_MAX       (max(PEN_SERVO_UP, PEN_SERVO_DOWN))
 
 
void servo_init()
{
  SERVO_PWM_DDR |= (1<<SERVO_PWM_BIT); // Configure as output pin.
  SERVO_TCCRA_REGISTER = (1<<COM2A1) | ((1<<WGM20) | (1<<WGM21));
  SERVO_TCCRB_REGISTER = (1<<CS22) | (1 <<CS21) | (1<<CS20);
  
  update_pen_from_z();
} 

void update_pen_from_z()
{
  float wpos_z = system_convert_axis_steps_to_mpos(sys_position, Z_AXIS) - gc_state.coord_system[Z_AXIS];  // get the machine Z in mm 
  
  // interpolate servo pulse based on z value
  int pulse_ticks = (int)((PEN_SERVO_RANGE * (wpos_z - Z_VALUE_PEN_DOWN) / Z_VALUE_PEN_RANGE) + PEN_SERVO_DOWN + 0.5f);

  // clip pulse to valid range and set servo pulse
  SERVO_OCR_REGISTER = max(PEN_SERVO_MIN, min(PEN_SERVO_MAX, pulse_ticks));
}

#endif // ifdef PEN_SERVO