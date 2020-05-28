% Tracé du pendule inverse avec contrôleurs (BF)
% Patrice Masson, 14 avril 2020

close all;

% Données du Workspace (de Simulink)

t  = x_cart.time;

xC = squeeze(x_cart.signals.values);

xB = squeeze(x_tip.signals.values);
yB = squeeze(y_tip.signals.values);

% Taille de la zone tracée
xmaxFigure =  ref_pos+0.2; 
xminFigure = -0.2; 
ymaxFigure =  2*L + w_radius + 0.1; 
yminFigure = -0.1; 

figure('NAME','Pendule inverse BF')
writerObj = VideoWriter('Pendule inverse BF.avi','Uncompressed AVI');
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