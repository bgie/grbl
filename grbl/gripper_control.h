/*
  gripper_control.h - gripper control methods
  Part of Grbl

  Copyright (c) 2021 Brecht Kuppens
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

#ifndef gripper_control_h
#define gripper_control_h

#define GRIPPER_NO_SYNC false
#define GRIPPER_FORCE_SYNC true

#define GRIPPER_STATE_DISABLE  0  // Must be zero.
#define GRIPPER_STATE_CW       bit(0)
#define GRIPPER_STATE_CCW      bit(1)


// Initializes gripper pins and hardware PWM, if enabled.
void gripper_init();

// Returns current gripper output state. Overrides may alter it from programmed states.
uint8_t gripper_get_state();

// Called by g-code parser when setting gripper state and requires a buffer sync.
#define gripper_sync(state, rpm) _gripper_sync(state)
void _gripper_sync(uint8_t state);

// Sets gripper running state with direction and enable.
#define gripper_set_state(state, rpm) _gripper_set_state(state)
void _gripper_set_state(uint8_t state);

// Stop and start gripper routines. Called by all gripper routines and stepper ISR.
void gripper_stop();


#endif
