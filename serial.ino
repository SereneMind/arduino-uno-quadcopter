/*---------------------------Serial Printing----------------------------------------------*/
void serialPrint() {


  /*------------------------------graphPlotter---------------------------*/
#ifdef graphPlotter
  Serial.print("\t");
  Serial.print(start_time);

  Serial.print("\t");
  Serial.print(accPitch);

  Serial.print("\t");
  Serial.print(gyroVecty_f);

  Serial.print("\t");
  Serial.print(Comp_pitch);
  /*-------------------------------------------------------*/
  Serial.print("\t");
  Serial.print(start_time);

  Serial.print("\t");
  Serial.print(accRoll);

  Serial.print("\t");
  Serial.print(gyroVectx_f);

  Serial.print("\t");
  Serial.println(Comp_roll);
#endif
  /*------------------------------end graphPlotter---------------------------*/

#ifdef anglevpwmGraph
  if (timeStep == start_time)
  {
    Serial.print("T \t Comp pitch \tComp roll \tesc_1 \tesc_2 \tesc_3 \tesc_4 \tThrottle ");
  }
  Serial.print("\t");
  Serial.print(start_time);
  Serial.print("\t");
  Serial.print(Comp_pitch);
  Serial.print("\t");
  Serial.print(Comp_roll);
  Serial.print("\t");
  Serial.print(esc_1);
  Serial.print("\t");
  Serial.print(esc_2);
  Serial.print("\t");
  Serial.print(esc_3);
  Serial.print("\t");
  Serial.print(esc_4);
  Serial.print("\t");
  Serial.println(throttle);
#endif

#ifdef accFinal
  Serial.print("ACC Pitch:  ");
  Serial.print(accPitch);
  Serial.print("\tACC Roll:  ");
  Serial.println(accRoll);
#endif


#ifdef accRaw
  Serial.print("ACC rawX:  ");
  Serial.print(xacc);
  Serial.print("\tACC rawY:  ");
  Serial.print(yacc);
  Serial.print("\tACC rawZ:  ");
  Serial.println(zacc);
#endif

#ifdef accVect
  Serial.print("ACC vectX:  ");
  Serial.print(vect_x);
  Serial.print("\tACC vectY:  ");
  Serial.print(vect_y);
  Serial.print("\tACC vectZ:  ");
  Serial.println(vect_z);
#endif

#ifdef accOffset
  Serial.print("\tACC offsets");
  Serial.println(accelero_yaw_cal);
#endif

#ifdef gyroFinal
  Serial.print("Gyro Pitch:  ");
  Serial.print(gyroVecty_f);
  Serial.print("\tGyro Roll:  ");
  Serial.print(gyroVectx_f);
  Serial.print("\tZ:  ");
  Serial.println(gyroVectz_f);
#endif

#ifdef gyroRaw
  Serial.print("Gyro rawX :  ");
  Serial.print(gyroRawx);
  Serial.print("\tGyro rawY:  ");
  Serial.print(gyroRawx);
  Serial.print("\tGyro rawZ:  ");
  Serial.println(gyroRawx);
#endif


#ifdef gyroVect
  Serial.print("Gyro vectX :  ");
  Serial.print(gyroVectx);
  Serial.print("\tGyro vectY:  ");
  Serial.print(gyroVecty);
  Serial.print("\tGyro vectZ:  ");
  Serial.println(gyroVectz);
#endif

#ifdef magnetoRAW
  Serial.print("x:  ");
  Serial.print(xMagF);
  Serial.print("y:  ");
  Serial.print(yMagF);
  Serial.print("z:  ");
  Serial.println(zMagF);
#endif

#ifdef finalAngles
  Serial.print("PITCH_f:  ");
  Serial.print(Comp_pitch);
  Serial.print("\tROLL_f:  ");
  Serial.print(Comp_roll);
  Serial.print("\tYAW_f:  ");
  Serial.println(accelero_yaw_cal);
#endif

#ifdef escValue
  Serial.print("\tesc_1  ");
  Serial.print(esc_1);
  Serial.print("\tesc_2  ");
  Serial.print(esc_2);
  Serial.print("\tesc_3  ");
  Serial.print(esc_3);
  Serial.print("\tesc_4  ");
  Serial.print(esc_4);
  Serial.print("\t");
  Serial.print(throttle);
  Serial.print("\t");
  Serial.print(i_am_up);
  Serial.print("\t");
  Serial.print(start_descend);
  Serial.print("\tcount  ");
  Serial.println(count);
#endif

#ifdef pidOutput
  Serial.print("\tPID pitch");
  Serial.print(pid_output_pitch);
  Serial.print("\tPid Roll:  ");
  Serial.println(pid_output_roll);
#endif

#ifdef sampleTime
  Serial.print("Timestep:  ");
  Serial.print(timeStep, DEC);
  Serial.print("\tstart_time:  ");
  Serial.print(start_time);
  Serial.print("   ");
  Serial.print("\tRestart Time");
  Serial.println(restart_time);

#endif

#ifdef pidError
  Serial.print("\tPID error roll:  ");
  Serial.print(pid_error_temp_roll);
  Serial.print("\tPID error pitch::");
  Serial.println(pid_error_temp_pitch);
#endif

}
