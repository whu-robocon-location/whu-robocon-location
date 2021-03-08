%INPUT: ��x������
%���ĵĲ����������־�ϵ��

%�뷨һ���˸�δ֪���˸�����
% syms X_POS BEITA MP CM1_POS CM1_NEG CM2_POS CM2_NEG ;
% syms K1_X_POS K2_X_POS K1_X_NEG K2_X_NEG K1_Y_POS K2_Y_POS K1_Y_NEG K2_Y_NEG;
% syms Angle_X Angle_Y;
% Position_Conds = [
%     cos(BEITA)*CM1_POS*K1_X_POS - sin(BEITA + MP)* CM2_NEG*K2_POS_X == 500;%X+
%     sin(BEITA)*CM1_POS*K1_X_POS  + cos(BEITA + MP)*CM2_NEG*K2_POS_X == 0;
%     cos(BEITA)*CM1_NEG*K1_X_NEG - sin(BEITA + MP)* CM2_POS*K2_NEG_X == -500;%X-
%     sin(BEITA)*CM1_NEG*K1_X_NEG  + cos(BEITA + MP)*CM2_POS*K2_NEG_X == 0;   
%     sin(BEITA)*CM1_POS*K1_Y_POS + cos(BEITA + MP)*CM2_POS*K2_Y_POS ==0;%Y+
%     cos(BEITA)*CM1_POS*K1_Y_POS - sin(BEITA + MP)*CM2_POS*K2_Y_POS == 500;
%     sin(BEITA)*CM1_NEG*K1_Y_NEG + cos(BEITA + MP)*CM2_NEG*K2_Y_NEG ==0;%Y-
%     cos(BEITA)*CM1_NEG*K1_Y_NEG - sin(BEITA + MP)*CM2_NEG*K2_Y_NEG == -500;
% ];


%1.ֻ�þ��뽨����ʧ������ͨ����ֵ��������
%2.�˸�δ֪���˸����̣����һ����ֵ�⡣ʵ�������Զ������Ķ࣬����ƽ����ģ���׼����
%3.����ʵ�鲻׼��ֱ���½��������飬�൱�ڷ���ʵ�ʽ�
% syms  CM1_POS CM1_NEG CM2_POS CM2_NEG ;

%������������ֻ��Ҫ��ֵ���־�ϵ��
syms K1_X_POS K2_X_POS K1_X_NEG K2_X_NEG K1_Y_POS K2_Y_POS K1_Y_NEG K2_Y_NEG;
syms CM1_POS  CM1_NEG  CM2_POS  CM2_NEG ��

%��ÿ����ľ������
X_POS_ERR = 1;
X_NEG_ERR =1 ;
Y_POS_ERR = 1;
Y_NEG_ERR =1;

%���������Լ���
MP = -0.00127046873;
BEITA = 0.7853981;

 %�־�ϵ����ֵ�����ڽ���������   
cm1_pos =0.0039978349 ;
cm1_neg = 0.0040002464;
cm2_pos = 0.0039848803;
cm2_neg =0.0039854631 ;

%����һ��������
Position_Conds =[
    cos(BEITA)*CM1_POS*K1_X_POS - sin(BEITA + MP)* CM2_NEG*K2_X_POS == 500,
    sin(BEITA)*CM1_POS*K1_X_POS  + cos(BEITA + MP)*CM2_NEG*K2_X_POS == 0,
    cos(BEITA)*CM1_NEG*K1_X_NEG - sin(BEITA + MP)* CM2_POS*K2_X_NEG == -500,
    sin(BEITA)*CM1_NEG*K1_X_NEG  + cos(BEITA + MP)*CM2_POS*K2_X_NEG == 0,
    sin(BEITA)*CM1_POS*K1_Y_POS + cos(BEITA + MP)*CM2_POS*K2_Y_POS ==500,
    cos(BEITA)*CM1_POS*K1_Y_POS - sin(BEITA + MP)*CM2_POS*K2_Y_POS == 0,
    sin(BEITA)*CM1_NEG*K1_Y_NEG + cos(BEITA + MP)*CM2_NEG*K2_Y_NEG ==-500,
    cos(BEITA)*CM1_NEG*K1_Y_NEG - sin(BEITA + MP)*CM2_NEG*K2_Y_NEG == 0;
 ];
vars = [K1_X_POS K2_X_POS K1_X_NEG K2_X_NEG K1_Y_POS K2_Y_POS K1_Y_NEG K2_Y_NEG];
[K1_X_POS K2_X_POS K1_X_NEG K2_X_NEG K1_Y_POS K2_Y_POS K1_Y_NEG K2_Y_NEG]=solve(subs(Position_Conds,{CM1_POS,CM1_NEG,CM2_POS,CM2_NEG},{cm1_pos,cm1_neg,cm2_pos,cm2_neg}),vars);

%�Խ����������ת��
K1_X_POS = eval(vpa(K1_X_POS,5));
K2_X_POS = eval(vpa(K2_X_POS,5));
K1_X_NEG =eval( vpa(K1_X_NEG,5));
K2_X_NEG = eval(vpa(K2_X_NEG,5));
K1_Y_POS = eval(vpa(K1_Y_POS,5));
K2_Y_POS = eval(vpa(K2_Y_POS,5));
K1_Y_NEG = eval(vpa(K1_Y_NEG,5));
K2_Y_NEG = eval(vpa(K2_Y_NEG,5));

%�����㷽��
F_X_POS = cos(BEITA) * CM1_POS * K1_X_POS - sin(BEITA + MP) * CM2_NEG * K2_X_POS;%X+
F_X_NEG = cos(BEITA) * CM1_NEG * K1_X_NEG - sin(BEITA + MP) * CM2_POS * K2_X_NEG;%X- 
F_Y_POS = sin(BEITA) * CM1_POS * K1_Y_POS + cos(BEITA + MP) * CM2_POS * K2_Y_POS;%Y+
F_Y_NEG = sin(BEITA) * CM1_NEG * K1_Y_NEG + cos(BEITA + MP) * CM2_NEG * K2_Y_NEG;%Y-

%�������������
X_POS_LOSE = (F_X_POS - (500*500/(500 + X_POS_ERR)))*(F_X_POS - (500*500/(500 + X_POS_ERR)));
X_NEG_LOSE = (F_X_NEG - (500*500/(-500 + X_NEG_ERR)))*(F_X_NEG - (500*500/(-500 + X_NEG_ERR)));
Y_POS_LOSE = (F_Y_POS - (500*500/(500 + Y_POS_ERR)))*(F_Y_POS - (500*500/(500 + Y_POS_ERR)));
Y_NEG_LOSE = (F_Y_NEG - (500*500/(-500 + Y_NEG_ERR)))*(F_Y_NEG - (500*500/(-500 + Y_NEG_ERR)));

%��ʧ����
F_LOSE  = X_POS_LOSE + X_NEG_LOSE + Y_POS_LOSE + Y_NEG_LOSE;

%Ѱ���½�����
GRAD_CM1_POS = diff(F_LOSE,'CM1_POS',1);
GRAD_CM1_NEG = diff(F_LOSE,'CM1_NEG',1);
GRAD_CM2_POS = diff(F_LOSE,'CM2_POS',1);
GRAD_CM2_NEG = diff(F_LOSE,'CM2_NEG',1);

%�ݶ��½��������û��ֲ����Լ���������
   h = 0.000000000001;%���ֲ���������ʵ�飬������С�˴�
   iter_num = 0;%��ǰ��������
   f_next = 0.2;%��һ�ε�����ֵ
    
    %���õ�����������
    max_iter_num = 1000;%����������
    threshold = 0.00001;%�ܽ��ܵ���С���

while( (iter_num < max_iter_num) && (f_next > threshold))

    %���㺯��ֵ
f_now= eval(vpa(subs(F_LOSE, {CM1_POS,CM1_NEG,CM2_POS,CM2_NEG},{cm1_pos,cm1_neg,cm2_pos,cm2_neg})));

grad_cm1_pos = eval(vpa(subs(GRAD_CM1_POS,{CM1_POS,CM1_NEG,CM2_POS,CM2_NEG},{cm1_pos,cm1_neg,cm2_pos,cm2_neg})));
grad_cm1_neg = eval(vpa(subs(GRAD_CM1_NEG,{CM1_POS,CM1_NEG,CM2_POS,CM2_NEG},{cm1_pos,cm1_neg,cm2_pos,cm2_neg})));
grad_cm2_pos = eval(vpa(subs(GRAD_CM2_POS,{CM1_POS,CM1_NEG,CM2_POS,CM2_NEG},{cm1_pos,cm1_neg,cm2_pos,cm2_neg})));
grad_cm2_neg = eval(vpa(subs(GRAD_CM2_NEG,{CM1_POS,CM1_NEG,CM2_POS,CM2_NEG},{cm1_pos,cm1_neg,cm2_pos,cm2_neg})));

    %�������������ݶ��½���
  cm1_pos = cm1_pos - h*grad_cm1_pos;
  cm1_neg = cm1_neg - h*grad_cm1_neg;
  cm2_pos = cm2_pos - h*grad_cm2_pos;
  cm2_neg = cm2_neg - h*grad_cm2_neg;
 
   f_next = eval(vpa(subs(F_LOSE, {CM1_POS,CM1_NEG,CM2_POS,CM2_NEG},{cm1_pos,cm1_neg,cm2_pos,cm2_neg})));
    
    iter_num  = iter_num + 1;
    
     fprintf("��ǰ��������Ϊ%d\n",iter_num);
     %disp(vpa(f_next))
      
     if(f_next<=f_now)
         f_min = f_next; 
         K = [vpa(f_min), vpa(cm1_pos),vpa(cm1_neg),vpa(cm2_pos),vpa(cm2_neg)];
          fprintf("���������У���ǰ��ʧ������ֵΪ%g\n",K(1));
     end
    
end

fprintf("������ɣ���ǰ��ʧ������ֵΪ%g\n",K(1));
fprintf("������ɣ���ǰcm1_posΪ%g\n",K(2));
fprintf("������ɣ���ǰcm1_neg��ֵΪ%g\n",K(3));
fprintf("������ɣ���ǰcm2_pos��ֵΪ%g\n",K(4));
fprintf("������ɣ���ǰcm2_neg��ֵΪ%g\n",K(5));