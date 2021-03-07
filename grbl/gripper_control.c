/*
  gripper_control.c - gripper control methods
  Part of Grbl

  Copyright (c) 2021 Brecht Kuppens
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


void gripper_init()
{
  GRIPPER_ENABLE_DDR |= (1<<GRIPPER_ENABLE_BIT); // Configure as output pin.
  GRIPPER_DIRECTION_DDR |= (1<<GRIPPER_DIRECTION_BIT); // Configure as output pin.
  gripper_stop();
}


uint8_t gripper_get_state()
{
  if (bit_istrue(GRIPPER_ENABLE_PORT,(1<<GRIPPER_ENABLE_BIT))) {
    return(GRIPPER_STATE_CW);
  }
  return(GRIPPER_STATE_DISABLE);
}


// Disables the gripper.
// Called by various main program and ISR routines. Keep routine small, fast, and efficient.
// Called by gripper_init(), gripper_set_speed(), gripper_set_state(), and mc_reset().
void gripper_stop()
{
  GRIPPER_ENABLE_PORT &= ~(1<<GRIPPER_ENABLE_BIT); // Set pin to low
  GRIPPER_DIRECTION_PORT |= (1<<GRIPPER_DIRECTION_BIT); // Set pin to high
}


// Immediately sets gripper running state.
// Called by g-code parser gripper_sync(), parking retract and restore, g-code program end,
// sleep, and gripper stop override.
void _gripper_set_state(uint8_t state)
{
  if (sys.abort) { return; } // Block during abort.

  if (state == GRIPPER_DISABLE) { // Halt or set gripper direction and rpm.
  
    gripper_stop();
  
  } else {
    
    GRIPPER_DIRECTION_PORT &= ~(1<<GRIPPER_DIRECTION_BIT);
    GRIPPER_ENABLE_PORT |= (1<<GRIPPER_ENABLE_BIT);
  }
  
  sys.report_ovr_counter = 0; // Set to report change immediately
}


// G-code parser entry-point for setting gripper state. Forces a planner buffer sync and bails 
// if an abort or check-mode is active.
void _gripper_sync(uint8_t state)
{
  if (sys.state == STATE_CHECK_MODE) { return; }
  protocol_buffer_synchronize(); // Empty planner buffer to ensure gripper is set when programmed.
  _gripper_set_state(state);
}

