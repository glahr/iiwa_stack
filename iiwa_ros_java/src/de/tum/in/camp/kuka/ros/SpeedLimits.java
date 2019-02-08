/**
 * Copyright (C) 2018 Arne Peters - arne.peters@tum.de Technische Universit�t M�nchen Chair for Robotics,
 * Artificial Intelligence and Embedded Systems Fakult�t f�r Informatik / I6, Boltzmannstra�e 3, 85748
 * Garching bei M�nchen, Germany http://www6.in.tum.de All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the
 * following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 * the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

package de.tum.in.camp.kuka.ros;

public class SpeedLimits {
  public static double jointVelocity;
  public static double jointAcceleration;
  public static double overrideJointAcceleration;

  public static double[] maxTranslationlVelocity = { 1000.0, 1000.0, 1000.0 };
  public static double[] maxOrientationVelocity = { 0.5, 0.5, 0.5 };

  public static double cartesianAcceleration = 200.0;
  public static double orientationAcceleration = 0.05;
  public static double cartesianJerk = 50;

  public static void init(Configuration configuration) {
    jointVelocity = configuration.getDefaultRelativeJointVelocity();
    jointAcceleration = configuration.getDefaultRelativeJointAcceleration();
    overrideJointAcceleration = 1.0;
  }

  public static void setPathParamters(double jointVelocity, double jointAcceleration, double overrideJointAcceleration) {
    SpeedLimits.jointVelocity = jointVelocity;
    SpeedLimits.jointAcceleration = jointAcceleration;
    SpeedLimits.overrideJointAcceleration = overrideJointAcceleration;
  }
}