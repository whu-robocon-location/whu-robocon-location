%����ʵ��õ�������������ʵ��������������ʵ��������ȫ���ϼ������̣���һ�����
%������ͨ�������������ʵ���������Ӷ�ȷ������ϵ��

digits(20)

global S0;%��������S0
syms K11 K12 K13 K14 K21 K22 K23 K24;

%                                           ��ֵ��,�ı��������뼴��
S0 = 180;   
k11 = -31936.75;                     %��x+ʱ����1������������ֵ��
k12 = 32010.75;                      %��x-ʱ����1��������
k13 = -31505;                        %��y+ʱ����1��������
k14 = 31504.25;                      %��y-ʱ����1��������
k21 = 31435.5;                       %��x+ʱ����2��������
k22 = -31408.5;                      %��x-ʱ����2��������
k23 = -32052.5;                      %��y+ʱ����2��������
k24 = 32030;                         %��y-ʱ����2��������
beita_period = -pi;                  %����arctan���������˻�����ڣ�����ʵ�����ѡ������
 
h = 5000;%���ֲ���������ʵ�飬ȡ�ϴ���ֲ���ʱ���нϺõ�������
max_iter_num = 200;%����������
threshold = 0.0000000001;%�ܽ��ܵ���С���


                                    %������ʧ����
%mp_angle_wrong
mp1 = atan((K11*K21+K13*K23)/(K23*K11 - K13*K21));
mp2 = -atan((K11*K21+K14*K24)/(K11*K24 - K14*K21));
mp3 = -atan((K12*K22+K13*K23)/(K12*K23 - K13*K22));
mp4 = atan((K12*K22+K14*K24)/(K24*K12 - K14*K22));
mp_ave = (mp1+mp2+mp3+mp4)/4;

%beita ���ݲ�ͬ�������beita��Ҫѡȡ��ͬ�Ľ��Լ�ѡ���������
beita1 = -atan(K21/K23) + beita_period ;
beita2 = atan(K21/K24)  + beita_period;
beita3 = atan(K22/K23) + beita_period;
beita4 = -atan(K22/K24)  + beita_period;
beita_ave = (beita1+beita2+beita3+beita4)/4;

%m���м����
m1 = -(K11*cos(beita1)+K13*sin(beita1))/(K21*sin(beita1+mp1)-K23*cos(beita1+mp1));
m2 = (K11*cos(beita2)+K14*sin(beita2))/(K21*sin(beita2+mp2)-K24*cos(beita2+mp2));
m3 = (K12*cos(beita3)+K13*sin(beita3))/(K22*sin(beita3+mp3)-K23*cos(beita3+mp3));
m4 = -(K12*cos(beita4)+K14*sin(beita4))/(K22*sin(beita4+mp4)-K24*cos(beita4+mp4));

%CM_PER_CNT
POS_CM_PER_CNT1 = -S0/(K14*sin(beita4) + m4*K24*cos(beita4+mp4));
NEG_CM_PER_CNT1 = S0/(K13*sin(beita1) + m1*K23*cos(beita1+mp1));
POS_CM_PER_CNT2 = -m2*S0/(K14*sin(beita2) + m2*K24*cos(beita2+mp2));
NEG_CM_PER_CNT2 = m3*S0/(K13*sin(beita3)+ m3*K23*cos(beita3+mp3));

%����������ƫ����
x1 = cos(beita_ave)*NEG_CM_PER_CNT1 *K11 - sin(beita_ave+mp_ave) *POS_CM_PER_CNT2*K21;%x+
y1 = sin(beita_ave)*NEG_CM_PER_CNT1*K11 + cos(beita_ave+mp_ave)*POS_CM_PER_CNT2*K21;
x2 = cos(beita_ave)*POS_CM_PER_CNT1*K12 - sin(beita_ave+mp_ave)*NEG_CM_PER_CNT2*K22;%x-
y2 = sin(beita_ave)*POS_CM_PER_CNT1*K12 + cos(beita_ave+mp_ave)*NEG_CM_PER_CNT2*K22;
x3 = cos(beita_ave)*NEG_CM_PER_CNT1*K13 - sin(beita_ave+mp_ave)*NEG_CM_PER_CNT2*K23;%y+
y3 = sin(beita_ave)*NEG_CM_PER_CNT1*K13 + cos(beita_ave+mp_ave)*NEG_CM_PER_CNT2*K23;
x4 = cos(beita_ave)*POS_CM_PER_CNT1*K14 - sin(beita_ave+mp_ave)*POS_CM_PER_CNT2*K24;%y-
y4 = sin(beita_ave)*POS_CM_PER_CNT1*K14 + cos(beita_ave+mp_ave)*POS_CM_PER_CNT2*K24;

%��ʧ����
f(K11,K12,K13,K14,K21,K22,K23,K24) = y1*y1 + y2*y2 + x3*x3 + x4*x4 + (x1-S0)*(x1-S0) + (x2+S0)*(x2+S0) + (y3-S0)*(y3-S0)+ (y4+S0)*(y4+S0);

%Ѱ���½�����
f11 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K11',1);
f12 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K12',1);
f13 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K13',1);
f14 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K14',1);
f21 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K21',1);
f22 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K22',1);
f23 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K23',1);
f24 = diff(f(K11,K12,K13,K14,K21,K22,K23,K24),'K24',1);

iter_num = 0;%��ǰ��������
f_next = 0.002;%��һ�ε�����ֵ
    
while( (iter_num < max_iter_num) && (f_next > threshold))

    %���㺯��ֵ
    f_now = eval(vpa(subs(f(k11,k12,k13,k14,k21,k22,k23,k24),{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));

    f11_now = eval(vpa(subs(f11,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    f12_now = eval(vpa(subs(f12,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    f13_now = eval(vpa(subs(f13,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    f14_now = eval(vpa(subs(f14,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    f21_now = eval(vpa(subs(f21,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    f22_now = eval(vpa(subs(f22,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    f23_now = eval(vpa(subs(f23,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    f24_now = eval(vpa(subs(f24,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));

    %�������������ݶ��½���
    k11 = k11 - h*f11_now;
    k12 = k12 - h*f12_now;
    k13 = k13 - h*f13_now;
    k14 = k14 - h*f14_now;
    k21 = k21 - h*f21_now;
    k22 = k22 - h*f22_now;
    k23 = k23 - h*f23_now;
    k24 = k24 - h*f24_now;
 
    f_next = eval(vpa(subs(f(k11,k12,k13,k14,k21,k22,k23,k24),{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24})));
    
    iter_num  = iter_num + 1;
    
     fprintf("��ǰ��������Ϊ%d\n",iter_num);
     %disp(vpa(f_next))
     
     if(f_next<=f_now)
         f_min = f_next; 
         K = [vpa(f_min), vpa(k11),vpa(k12),vpa(k13),vpa(k14),vpa(k21),vpa(k22),vpa(k23),vpa(k24)];
          fprintf("���������У���ǰ��ʧ������ֵΪ%g\n",K(1));
     end
    
end
%��������
M = [vpa(eval((subs(beita_ave,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24}))));
    vpa(subs(mp_ave,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24}));
    vpa(subs(POS_CM_PER_CNT1,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24}));
    vpa(subs(POS_CM_PER_CNT2,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24}));
    vpa(subs(NEG_CM_PER_CNT1,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24}));
    vpa(subs(NEG_CM_PER_CNT2,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24}))];


% disp(vpa(eval(subs(m4,{K11,K12,K13,K14,K21,K22,K23,K24},{k11,k12,k13,k14,k21,k22,k23,k24}))))
 fprintf("������ɣ�K11(��x+������1����������Ϊ%f\n",K(2));
 fprintf("������ɣ�K12(��x-������1����������Ϊ%f\n",K(3));
 fprintf("������ɣ�K13(��y+������1����������Ϊ%f\n",K(4));
 fprintf("������ɣ�K14(��y-������1����������Ϊ%f\n",K(5));
 fprintf("������ɣ�K21(��x+������2����������Ϊ%f\n",K(6));
 fprintf("������ɣ�K22(��x-������1����������Ϊ%f\n",K(7));
 fprintf("������ɣ�K23(��y+������1����������Ϊ%f\n",K(8));
 fprintf("������ɣ�K24(��y-������2����������Ϊ%f\n",K(9));
 
 fprintf("POS_CM_PER_CNT1Ϊ%20.10f\n",M(3));
 fprintf("POS_CM_PER_CNT2Ϊ%20.10f\n",M(4));
 fprintf("NEG_CM_PER_CNT1Ϊ%20.10f\n",M(5));
 fprintf("NEG_CM_PER_CNT2Ϊ%20.10f\n",M(6));
 fprintf("beita_aveΪ%20.10f\n",M(1));
 fprintf("mp_aveΪ%20.11f\n",M(2));
% text('Interpreter','latex','position',[0,5],'string',['��ǰ����ʧ������ֵΪ',latex(K(1))])




