% Tracé du pendule inverse (BO)
% Patrice Masson, 19 mai 2020

close all;

% Données de MotionGenesis

Pendule_BO = load('MG_Model_BO.1'); 

% Redéfinition des variables lues dans le fichier
t  = Pendule_BO(:,1);

xC = Pendule_BO(:,2);

xB = Pendule_BO(:,3);
yB = Pendule_BO(:,4);

% Taille de la zone tracée
xmaxFigure =  ref_pos+0.2; 
xminFigure = -0.2; 
ymaxFigure =  2*L + w_radius + 0.1; 
yminFigure = -0.1; 

figure('NAME','Pendule inverse BO')
writerObj = VideoWriter('Pendule inverse BO.avi','Uncompressed AVI');
open(writerObj);

for i = 1:5:length(t)
    
    % Tracé pendule
    plot([xC(i,1) xB(i,1)]', [w_radius yB(i,1)]','-','LineWidth',5)
    
    % Tracé roues
    rectangle('Position',[xC(i,1)-w_radius, 0, w_radius*2, w_radius*2],...
              'Curvature',[1,1],'FaceColor','none');
    hold on
    
    % Trace de l'extrémité
    plot(xB(1:i), yB(1:i),'-','LineWidth',1)
    
    % Tracé du sol
    line([xminFigure xmaxFigure], [0 0]);
    
    axis equal
    axis([xminFigure xmaxFigure yminFigure ymaxFigure])
    hold off
    
    pause(0.005)
    
    frame = getframe;
    writeVideo(writerObj,frame);
    
end

close(writerObj);