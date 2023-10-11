from aip import AipSpeech
import os
import requests
from lxml import etree
import random
import paho.mqtt.client as mqtt
import time
import RPi.GPIO as GPIO


#申请百度语音识别
APP_ID = '28745995'
API_KEY = 'vH0XPKgeWLWsRL08NIlGvcxz'
SECRET_KEY = 'LFYCW131eD1vkYq4ZLop7PGNGq41NFLh'

client_id="remote-control"
mqtt_remote_ip = "test.ranye-iot.net"
 
client = AipSpeech(APP_ID, API_KEY, SECRET_KEY)

colors = [0xFF00, 0x00FF, 0x0FF0, 0xF00F]
makerobo_pins = (11, 12)  # PIN管脚字典

GPIO.setmode(GPIO.BOARD)     # 采用实际的物理管脚给GPIO口
GPIO.setwarnings(False)      # 去除GPIO口警告
GPIO.setup(makerobo_pins, GPIO.OUT)   # 设置Pin模式为输出模式
# GPIO.output(makerobo_pins, GPIO.LOW)  # 设置Pin管脚为低电平(0V)关闭LED
 
# 读取文件
def get_file_content(filePath):
     with open(filePath, 'rb') as fp:
        return fp.read()

# 语音合成
def tts(strw):
        answer = client.synthesis(strw,'zh',1, {'vol': 5,'per':0,})
        if not isinstance(answer, dict):
                with open('answer_word.mp3', 'wb') as f:
                        f.write(answer)
                f.close()
                print('tts successful')

# 控制led        
def led(num):
    if num == '0':
        # print(num)
        GPIO.output(makerobo_pins[0],GPIO.HIGH)
    elif num == '1':
        GPIO.output(makerobo_pins[1],1)
    elif num == '2':
        GPIO.output(makerobo_pins[0],0)
    elif num == '3':
        GPIO.output(makerobo_pins[1],0)

def pick_city(word):
        if '深圳' in word:
                return 'shenzhen'
        elif '北京' in word:
                return 'beijing'
        elif '上海' in word:
                return 'shanghai'
        elif '广州' in word:
                return 'guangzhou'
        else:
                return 'shenzhen'

def weather(word):    
        city = pick_city(word)
        # 目标网址
        url = 'https://www.tianqi.com/%s/'%city
        # 请求头，伪装成浏览器
        headers = {
                'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36'
                }
        # 向网址发送请求并获取数据
        response = requests.get(url=url,headers=headers)
        # 筛选信息
        data = etree.HTML(response.text)
        weather_list =  data.xpath('//dl[@class="weather_info"]//text()')
        
        time = weather_list[5]
        city = weather_list[2]
        weather = weather_list[12]
        temperature = weather_list[13]
        wet = weather_list[16]
        wind = weather_list[17]
        air = weather_list[20]
        
        weather_str = '今天是'+time+','+city+','+weather+',温度'+temperature+','+wet+','+wind+','+air
        
        return weather_str

#mqtt连接
def connect_mqtt_remote():
        def on_connect(client, userdata, flags, rc):
                if rc == 0:
                        print("Connected to MQTT remote Broker!")
                else:
                        print("Failed to connect, return code %d\n", rc)

        client_remote = mqtt.Client(client_id)
        client_remote.on_connect = on_connect
        client_remote.connect(mqtt_remote_ip, 1883)
        return client_remote

def publish(client, num):
        if num==0:
                topic='raspiberry-remote-42453/online'
                payload = '1'
                result = client.publish(topic, payload)
        if num==1:
                topic='AC/control/switch'
                payload= '1'
                result = client.publish(topic, payload)
        if num==2:
                topic = 'AC/control/switch'
                payload = '0'
                result = client.publish(topic, payload)
        # result: [0, 1]
        status = result[0]
        if status == 0:
                print(f"Send 1 to topic `{topic}`")
        else:
                print(f"Failed to send message to topic {topic}")
          

def do_something(word, client):
        if ('开' in word) and ('空调' in word):
                # '好的，这就为您开灯。'
                os.system('mplayer ./resources/open_light.mp3')
                led('1')
                publish(client,1)
        elif ('关' in word) and ('灯' in word):
                # '好的，这就为您关灯。'
                os.system('mplayer ./resources/close_light.mp3')
                led('3')
        elif '天气' in word:
                answer_tts = weather(word)
                tts(answer_tts)
                os.system('mplayer answer_word.mp3')
        elif '聊天' in word:
                # 调用图灵机器人
                os.system('python3 tuling_demo.py')
        else:
                # 不好意思，没听清，能再说一遍吗
                os.system('mplayer ./resources/no_idea.mp3')
                        


if __name__ == "__main__":
        client_remote = connect_mqtt_remote()
        a=random.randint(0,200)
        if(a%3==0):
                os.system('mplayer ./resources/answer1.mp3')
        elif(a%3==1):
                os.system('mplayer ./resources/answer2.mp3')
        else:
                os.system('mplayer ./resources/answer3.mp3')
                
        print("="*50)
        print()
        print("开始录音:")
        os.system('arecord -d 3 -r 16000 -c 1 -f S16_LE listen_word.wav')

        # 识别本地文件
        path='.'
        result = client.asr(get_file_content(path+'/listen_word.wav'), 'wav', 16000, {'dev_pid': 1536, })

        print(result)
        if(result['err_msg']=='success.'):
                # print('bbb')
                word=result['result']
                do_something(word[0], client_remote)
        else:
                os.system('mplayer ./resources/no_idea.mp3')
        publish(client_remote,0)
        client_remote.loop_start()
        # client_remote.disconnect()
        # client.disconnect()
        # time.sleep(30)
