%Բ��������ʵ����һֱ����������Ϊ�ǻ�е��ģ�����Ĳ�׼���µ���������Ҫ����x��y���õ���ȷ��ϵ��
%����k1��k2�Ĳ��Ϊ��ֵ��Բ�����������ú��١�����ʵ��ɹ�����

digits(20)

syms X Y
%                                       ��ֵ����

x= 0;                     %��180���Ժ�С��x����ĸı�������ֵ�ǻ�е������ģ�Ͳ���
y = -98.12045;                %��180���Ժ�С��x����ĸı�������ֵ�ǻ�е������ģ�Ͳ���

K1_POS = 0.475318819 + x;    %��ת180��ʱ���������K1��ֵ��ע�⣬�����е�K��Ӧ��ʵ������ARC_K1_POS
K2_POS = 9.662813507 + y;       %��ת180��ʱ���������K2��ֵ
K1_NEG = 0.153768617 + x;    %��ת180��ʱ���������K1��ֵ
K2_NEG = 9.70980014 + y;       %��ת180��ʱ���������K2��ֵ

a_pos_period = -pi;              %����tan�������������������Ҫ�����ڡ������ʵ��Ϊ90�㣬��ת���������-90�㣬�Ǿ����_pos_period = pi
a_neg_period = -pi;               %�����ʵ��Ϊ90�㣬��ת���������-90�㣬�Ǿ����_neg_period = pi��һ����˵��neg��pos��һ���ǡ�pi����һ������0

% �ݶ��½�(����x��y)�����޸�

h = 10000;                           %���ֲ���������ʵ�飬ȡ�ϴ���ֲ���ʱ���нϺõ�����
max_iter_num = 20;             %����������

x_max = 0.2;
x_min = -0.2;
y_max = -97.92;
y_min = -98.32;


%                                       ��������

%Ϊ��֤��ʧ����������Ȩֵһ����L,a�������б仯�������þ����ֵ���Ծ���ľ�ֵ��8��һ��Ҳ��Ҫ��һ��
a_POS = atan((K2_POS - Y)/(K1_POS - X)) + a_pos_period;
a_NEG = atan((K2_NEG - Y)/(K1_NEG - X)) + a_neg_period;
L_POS = (sqrt((K1_POS - X)*(K1_POS - X) +( K2_POS - Y)*(K2_POS- Y)) / 2) / (-3.114);
L_NEG = (sqrt((K1_NEG - X)*(K1_NEG - X) +( K2_NEG - Y)*(K2_NEG- Y)) / 2) / (-3.114);

F = (a_POS-  a_NEG)*(a_POS -  a_NEG) +(L_POS - L_NEG)* (L_POS - L_NEG);

Fx = diff(F,'X',1);
Fy = diff(F,'Y',1);

iter_num = 0;                   %��ǰ��������
threshold = 0.0000000001;       %�ܽ��ܵ���С���
f_next = 0.1;                   %��һ�ε�����ֵ,ֻҪ����threshold���ɣ�����threshold���ģ����Ҳ�����޸�
f_min = 0;
f_begin = eval(vpa(subs(F,{X,Y},{x,y})));

circle(1) = subs(a_POS,{X,Y},{x,y});
circle(2) = subs(a_NEG,{X,Y},{x,y});
circle(3) = subs(L_POS*(-3.114),{X,Y},{x,y});
circle(4) = subs(L_NEG*(-3.114),{X,Y},{x,y});

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
             circle(3) = subs(L_POS*(-3.114),{X,Y},{x,y});
             circle(4) = subs(L_NEG*(-3.114),{X,Y},{x,y});
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
