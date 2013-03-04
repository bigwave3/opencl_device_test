/*
 * Copyright (C) 2010 Matthew Scarpino
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at 
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 */

package com.ee.cldevicetest;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.ee.cldevicetest.R;

import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;

/** 
* This Activity calls on the Native Development Kit and OpenCL
* to acquire information about an OpenCL-compliant device 
*
* @author Matthew Scarpino
* @version 0.1 March 3, 2013.
*/
public class CLDeviceTestActivity extends Activity {

  static boolean sfoundLibrary = true;
  
  static {
    try {
      System.load("/system/vendor/lib/egl/libGLES_mali.so");
      System.loadLibrary("CLDeviceTest");  
    }
    catch (UnsatisfiedLinkError e) {
      sfoundLibrary = false;
    }
  }

  /** Calls OpenCL commands to test the GPU */
  private native int updateBuffer(ByteBuffer buff);

  /** Creates and configures the Activity */
  public void onCreate(Bundle b) {
    super.onCreate(b);
    setContentView(R.layout.devicetest);

    // Set introductory message
    TextView introMsg = (TextView)findViewById(R.id.intro);
    if(sfoundLibrary) {
      introMsg.setText(R.string.welcome);
    }
    else {
      introMsg.setText(R.string.error);
      return;
    }
      
    // Allocate and update buffer
    ByteBuffer buffer = ByteBuffer.allocateDirect(8192);
    updateBuffer(buffer);
    String resultString = "";
    try {
      resultString = new String(buffer.array(), "UTF-8");
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    }

    // Access fields of comma-separated array
    int[] ids = 
      {R.id.tv1, R.id.tv2, R.id.tv3, R.id.tv4, R.id.tv5, R.id.tv6, R.id.tv7, R.id.tv8,
        R.id.tv9, R.id.tv10, R.id.tv11, R.id.tv12, R.id.tv13, R.id.tv14, R.id.tv15, R.id.tv16,
        R.id.tv17, R.id.tv18, R.id.tv19, R.id.tv20, R.id.tv21, R.id.tv22, R.id.tv23, R.id.tv24};
    String[] names = new String[]{"Name", "Vendor", "Supported OpenCL version", 
        "Maximum clock frequency", "Maximum number of compute units", "Maximum work-group size", 
        "Maximum size of global memory", "Maximum size of local memory", "Image support", 
        "Maximum width of 2-D images", "Maximum height of 2-D images", "Supported extensions"};
    String[] values = resultString.split(",");

    for(int i=0; i<names.length; i++) {
      ((TextView)findViewById(ids[2*i])).setText(names[i]);
      ((TextView)findViewById(ids[2*i+1])).setText(values[i]);
    }
  }
}
