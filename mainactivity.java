package com.example.tracking;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    int MY_PERMISSIONS_REQUEST_SEND_SMS=1;
    TextView tvResults;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tvResults= findViewById(R.id.tvResults);
        tvResults.setVisibility(View.GONE);

    }

    public void btn_SendSMS_OnClick(View view) {

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.SEND_SMS) != PackageManager.PERMISSION_GRANTED) {

            ActivityCompat.requestPermissions(this,new String[]{Manifest.permission.SEND_SMS}, MY_PERMISSIONS_REQUEST_SEND_SMS);
        }
        else{
            SmsManager sms= SmsManager.getDefault();
            sms.sendTextMessage("+4915205910439",null,"Track",null,null);
            String results= "A google-maps link will be sent to you shortly";
            tvResults.setText(results);
            tvResults.setVisibility(View.VISIBLE);
        }

    }
}
