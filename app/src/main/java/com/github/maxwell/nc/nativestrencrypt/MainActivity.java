package com.github.maxwell.nc.nativestrencrypt;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.github.maxwell.nc.encryptlib.EncryptUtils;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /**
     * 按钮点击事件
     */
    public void onButtonClick(View view) {
        getPassword();
    }

    /**
     * so调用例子
     */
    public void getPassword() {
        TextView tvPass = (TextView) findViewById(R.id.tv_pass);

        String samplePass = EncryptUtils.getSamplePass(this);//获取密码
        if (samplePass.equals("error")) {
            tvPass.setText("获取结果：非合法应用调用！");
        } else {
            tvPass.setText(String.format("获取结果：%s", samplePass));
        }
    }
}
