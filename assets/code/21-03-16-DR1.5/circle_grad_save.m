%%
%Բ��������ʵ����һֱ����������Ϊ�ǻ�е��ģ�����Ĳ�׼���µ���������Ҫ����x��y���õ���ȷ��ϵ��
%����k1��k2�Ĳ��Ϊ��ֵ��Բ�����������ú��١�����ʵ��ɹ�����
clc;
clear;
digits(20);

syms X Y;

%%                                       ��ֵ����
x = -93.079559;% -93.1;                 %��180���Ժ�С��x����ĸı�������ֵ�ǻ�е������ģ�Ͳ���
y = 23.658180;%23.61818;                %��180���Ժ�С��x����ĸı�������ֵ�ǻ�е������ģ�Ͳ���

K1_POS = -7.23790026 + x;       %��ת180��ʱ���������K1��ֵ��ע�⣬�����е�K��Ӧ��ʵ������ARC_K1_POS
K2_POS = -9.4043932 + y;        %��ת180��ʱ���������K2��ֵ
K1_NEG = -7.13233232 + x;       %��ת180��ʱ���������K1��ֵ
K2_NEG = -9.26155376 + y;       %��ת180��ʱ���������K2��ֵ

a_pos_period = 0;               %����tan�������������������Ҫ�����ڡ������ʵ��Ϊ90�㣬��ת���������-90�㣬�Ǿ����_pos_period = pi
a_neg_period = 0;               %�����ʵ��Ϊ90�㣬��ת���������-90�㣬�Ǿ����_neg_period = pi��һ����˵��neg��pos��һ���ǡ�pi����һ������0

% �ݶ��½�(����x��y)�����޸�

h = 1000000;                   %���ֲ�����ȡ����ֲ�������fx_now������Ϊn�Σ�h������Ϊ2-n
max_iter_num = 50;             %����������
error_permitted = 0.1;        %��������װ�����
scale = 6;                     %L/��
%%                                      ��������

%Ϊ��֤��ʧ����������Ȩֵһ����L,a�������б仯�������þ����ֵ���Ծ���ľ�ֵ��8��һ��Ҳ��Ҫ��һ��
a_POS = atan((K2_POS-Y)/(K1_POS - X)) + a_pos_period;
a_NEG = atan((K2_NEG-Y)/(K1_NEG - X)) + a_neg_period;
L_POS = (sqrt((K1_POS - X)*(K1_POS - X) +( K2_POS - Y)*(K2_POS- Y)) / 2) / scale;
L_NEG = (sqrt((K1_NEG - X)*(K1_NEG - X) +( K2_NEG - Y)*(K2_NEG- Y)) / 2) / scale;

F = (a_POS-  a_NEG)*(a_POS -  a_NEG) +(L_POS - L_NEG)* (L_POS - L_NEG);

Fx = diff(F,'X',1);
Fy = diff(F,'Y',1);

iter_num = 0;                   %��ǰ��������
threshold = 0.0000000001;       %�ܽ��ܵ���С���
f_next = 0.1;                   %��һ�ε�����ֵ,ֻҪ����threshold���ɣ�����threshold���ģ����Ҳ�����޸�
f_min = 0;
f_begin = eval(vpa(subs(F,{X,Y},{x,y})));

x_max = x + error_permitted;
x_min = x - error_permitted;
y_max = y + error_permitted;
y_min = y - error_permitted;
count = 0;
while( (iter_num < max_iter_num) && (f_next > threshold))

    %���㺯��ֵ
    f_now = eval(vpa(subs(F,{X,Y},{x,y})));

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
              circle(3) = subs(L_POS*scale,{X,Y},{x,y});
              circle(4) = subs(L_NEG*scale,{X,Y},{x,y});
         end
    else
        h = h/10;
        x = x_last - h*fx_now;
        y = y_last - h*fy_now;
        count = count + 1;
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
