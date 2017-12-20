function [millistem, indexarr] = analysedata(filenamep, modep, risecutp, fallcutp, plotoffsetp)

%filenamep = '/home/zmann/gqrx-aufnahmen/gqrx-20160403-094036.wav';
%risecutp = 2;
%fallcutp = 2;
%fullanalysisp = 1;

filename = filenamep;
risecut=risecutp;
fallcut=-fallcutp;
mode = modep;

[samples, frequency] = wavread(filename);
dispstr = ['++Analysing ', filename]
disp(dispstr);
dispstr = ['.frequency: ', num2str(frequency)];
disp(dispstr);
plotoffset = plotoffsetp*frequency/1000;

if ndims(samples) == 2
    disp('+extracting left channel of stereo-signal');
    samples = samples(:,1);
end


h = [1, 2, 2, 3, 3, 3, 5, 5, 5, 5, 5, 3, 3, 3, 2, 2, 1];

disp('+convolution of the data for a better signal to work with');
convolved = conv(samples, h);

disp('+derivate signal');
difference = diff(convolved);


topline = [];
bottomline = [];

topbool = 0;
bottombool = 0;

rising = [];
falling = [];

disp('+search for the edges of the signal (falling and rising seperate)');
for i = 1:1:length(difference)
topline(end+1)=0;
bottomline(end+1)=0;
if (difference(i) > risecut && topbool == 0)
topline(end) = difference(i);
rising(end+1) = i;
topbool=1;
bottombool=0;
end
if (difference(i) < fallcut && bottombool == 0)
bottomline(end) = difference(i);
falling(end+1) = i;
topbool=0;
bottombool=1;
end
end


dispstr = ['+cut the samples into seperate signals (time gap: ', num2str(plotoffset*1000/frequency), ' milliseconds)'];
disp(dispstr);
h2 = ones([1 plotoffset]);
areatoplot = conv(topline, h2);
areatoplotshiftet = circshift(areatoplot, [0 -plotoffset/2]);

%erase the 0-spots of topline and bottomline
topline(topline == 0) = NaN;
bottomline(bottomline == 0) = NaN;

%erase one point from rising or falling, so that both can be handled in one loop
if length(rising) > length(falling)
    rising=rising(1:length(rising)-1);
end
if length(falling) > length(rising)
    falling=falling(1:length(falling)-1);
end

%figure out if signal starts with a rising or falling edge
if (rising(1) < falling(1))
    hills = falling - rising;
    tales = rising(2:length(rising)) - falling(1:length(falling)-1);
else
    tales = rising - falling;
    hills = falling(2:length(falling)) - rising(1:length(rising)-1);
end


hillsmilli= hills*1000/frequency;
talesmilli= tales*1000/frequency;

disp('+obtaining the data for the stem-plot')
millistem = [];
if length(hillsmilli) > length(talesmilli)
    for i = 1:1:length(talesmilli)-1
        millistem(end+1)=hillsmilli(i);
        millistem(end+1)=-talesmilli(i);
    end
    millistem(end+1)=hillsmilli(i);
else
    for i = 1:1:length(hillsmilli)-1
        millistem(end+1)=-talesmilli(i);
        millistem(end+1)=hillsmilli(i);
    end
    millistem(end+1)=-talesmilli(i);
end

disp('+figure out how many plots will be shown');
diagrammcounter=1;
stemgap = plotoffset*1000/frequency;
for i = 1:1:length(millistem)
    if abs(millistem(i)) > stemgap
        diagrammcounter=diagrammcounter+1;
    end
end
dispstr = ['.', num2str(diagrammcounter), ' figures'];
disp(dispstr);
if diagrammcounter > 10
    disp('--Too many figures');
    return
end

disp('+start displaying analysis');
close all;
if mode == 1 || mode == 3
disp('.displaying the time-domain-data');
index = [1 1];
up = 0;
figurecounter = 1;
for i = 1:1:length(samples)
    if areatoplotshiftet(i) > 0 && up == 0
        up = 1;
        index(1)=i;
    end
    if ((areatoplotshiftet(i) == 0 || i == length(samples)) && up == 1)
        up = 0;
        index(2)=i;
        figure(figurecounter);
        figurecounter=figurecounter+2;
        hold;
        plot(difference(index(1):index(2)), 'g');
        plot(samples(index(1):index(2)), 'r');
        plot(topline(index(1):index(2)), 'o');
        plot(bottomline(index(1):index(2)), 'o');
    end
end
end



if mode == 2 || mode == 3
indexarr = [1 1; 1 1; 1 1; 1 1; 1 1; 1 1; 1 1; 1 1; 1 1; 1 1];
indexarrcounter=1;
disp('.displaying durations of the analysed + and - areas');
currentmaxduration=0;
gridsteparray=[0.1, 0.2, 0.5, 1, 2, 5, 10];
gridstep=20;
figurecounter=2;
for i = 1:1:length(millistem)
    absms = abs(millistem(i));
    if absms > stemgap
        indexarr(indexarrcounter,2)=i-1;
        for j = 1:1:length(gridsteparray)
            if currentmaxduration/5 > gridsteparray(length(gridsteparray)-j)
                gridstep=gridsteparray(length(gridsteparray)-j);
                break;
            end
        end
        currentmaxduration=0;
        figure(figurecounter);
        figurecounter=figurecounter+2;
        stem(millistem(indexarr(indexarrcounter,1):indexarr(indexarrcounter,2)));
        ay = gca;
        set(ay, 'YTick', (-50:gridstep:50));
        ylabel('milliseconds');
        grid on;
        indexarrcounter=indexarrcounter+1;
        indexarr(indexarrcounter,1)=i+1;
        gridstep=20;
    else
    if absms > currentmaxduration
        currentmaxduration=absms;
    end
    end
end
    for j = 1:1:length(gridsteparray)
        if currentmaxduration/5 > gridsteparray(length(gridsteparray)-j)
            gridstep=gridsteparray(length(gridsteparray)-j);
            break;
        end
    end
    figure(figurecounter);
    figurecounter=figurecounter+2;
    indexarr(indexarrcounter,2)=length(millistem);
    stem(millistem(indexarr(indexarrcounter,1):indexarr(indexarrcounter,2)));
    ay = gca;
    set(ay, 'YTick', (-50:gridstep:50));
    ylabel('milliseconds');
    grid on;
end