%Բ��������ʵ����һֱ����������Ϊ�ǻ�е��ģ�����Ĳ�׼���µ���������Ҫ����x��y���õ���ȷ��ϵ��
%����k1��k2�Ĳ��Ϊ��ֵ��Բ�����������ú��١�����ʵ��ɹ�����

digits(20)

syms X Y R THETA;
%                                       ��ֵ����
 x= 0.02335;                     %��180���Ժ�С��x����ĸı�������ֵ�ǻ�е������ģ�Ͳ���
 y = -104.810688;                %��180���Ժ�С��y����ĸı�������ֵ�ǻ�е������ģ�Ͳ���

K1_POS = -13.94717351 + x;    %��ת180��ʱ���������K1��ֵ��ע�⣬�����е�K��Ӧ��ʵ������ARC_K1_POS
K2_POS = -14.4707069 + y;       %��ת180��ʱ���������K2��ֵ
K1_NEG = -14.22696467 + x;    %��ת180��ʱ���������K1��ֵ
K2_NEG = -14.4069862 + y;       %��ת180��ʱ���������K2��ֵ

a_pos_period = 0;              %����tan�������������������Ҫ�����ڡ������ʵ��Ϊ90�㣬��ת���������-90�㣬�Ǿ����_pos_period = pi
a_neg_period = 0;               %�����ʵ��Ϊ90�㣬��ת���������-90�㣬�Ǿ����_neg_period = pi��һ����˵��neg��pos��һ���ǡ�pi����һ������0

% �ݶ��½�(����x��y)�����޸�

h = 10000;                           %���ֲ���������ʵ�飬ȡ�ϴ���ֲ���ʱ���нϺõ�����
max_iter_num = 50;             %����������

x_max = 1;
x_min = -1;
y_max = -102;
y_min = -106;


%                                       ��������

%Ϊ��֤��ʧ����������Ȩֵһ����L,a�������б仯�������þ����ֵ���Ծ���ľ�ֵ��8��һ��Ҳ��Ҫ��һ��
R = sqrt(X*X + Y*Y);
THETA = atan(Y/X);
X_POS = -2*R - X*cos(179.9*pi/180 - THETA) + Y*sin(THETA);%180.01��Ӧ��ת180��С��ֵ������
Y_POS = X*sin(179.9*pi/180 - THETA) + X*sin(THETA);
X_NEG = -2*R - X*cos(180.1*pi/180 - THETA) + Y*sin(THETA);
Y_NEG = X*sin(180.1*pi/180 - THETA) + X*sin(THETA);
a_POS = atan((K2_POS - Y_POS)/(K1_POS - X_POS)) + a_pos_period;
a_NEG = atan((K2_NEG- Y_NEG)/(K1_NEG - Y_NEG)) + a_neg_period;
L_POS = (sqrt((K1_POS - X_POS)*(K1_POS - X_POS) +( K2_POS - Y_POS)*(K2_POS- Y_POS)) / 2) / 4;
L_NEG = (sqrt((K1_NEG - X_NEG)*(K1_NEG - X_NEG) +( K2_NEG - Y_NEG)*(K2_NEG- Y_NEG)) / 2) / 4;

%F = (abs(a_POS) - abs( a_NEG))*(abs(a_POS) - abs( a_NEG)) +  (L_POS - L_NEG)* (L_POS - L_NEG);
F = (a_POS-  a_NEG)*(a_POS -  a_NEG) +(L_POS - L_NEG)* (L_POS - L_NEG);
%F =  (L_POS - L_NEG)* (L_POS - L_NEG);

Fx = diff(F,'X',1);
Fy = diff(F,'Y',1);

iter_num = 0;                   %��ǰ��������
threshold = 0.0000000001;       %�ܽ��ܵ���С���
f_next = 100;                   %��һ�ε�����ֵ,ֻҪ����threshold���ɣ�����threshold���ģ����Ҳ�����޸�
f_min = 0;
f_begin = eval(vpa(subs(F,{X,Y},{x,y})));

while( (iter_num < max_iter_num) && (f_next > threshold))

    %���㺯��ֵ
    f_now = f_next;

    fx_now =  eval(vpa(subs(Fx,{X,Y},{x,y})));
    fy_now =  eval(vpa(subs(Fy,{X,Y},{x,y})));

    %����x��yֵ���ݶ��½���
    if ( x>x_min && x<x_max && y>y_min && y<y_max)
         x_last = x;
         y_last = y;
         
         x = x - h*fx_now;
         y = y - h*fy_now;
         
        f_next = eval(vpa(subs(F,{X,Y},{x,y})));    
        iter_num  = iter_num + 1;    
        fprintf("��ǰ��������Ϊ%d\n",iter_num);

         if(f_next<=f_now)
              f_min = f_next; 
              K = [vpa(f_min), vpa(x),vpa(y)];
              fprintf("���������У���ǰ��ʧ������ֵΪ%g\n",K(1));
              circle(1) = subs(a_POS,{X,Y},{x,y});
              circle(2) = subs(a_NEG,{X,Y},{x,y});
              circle(3) = subs(L_POS*4,{X,Y},{x,y});
              circle(4) = subs(L_NEG*4,{X,Y},{x,y});
         end
    else
        h = h/10;
        
        x = x_last - h*fx_now;
        y = y_last - h*fy_now;
         
    end
end
    
 fprintf("��ʧ����F�ĳ�ֵ��%f\t",vpa(f_begin));
 fprintf("��ʧ����F���ڵ�ֵ��%f\n",vpa(f_min));
 fprintf("ת180���С������X�ĸı�����%f\t",vpa(x));
 fprintf("ת180���С������Y�ĸı�����%f\n",vpa(y));
 
 fprintf("��ת�õ��Ħ�ֵa_POS��%f\t",vpa(circle(1)));
 fprintf("��ת�õ��Ħ�ֵa_NEG��%f\n",vpa(circle(2)));
 fprintf("��ת�õ���LֵL_POS��%f\t",vpa(circle(3)));
 fprintf("��ת�õ���LֵL_NEG��%f\n",vpa(circle(4)));
