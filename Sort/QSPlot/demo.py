# coding: utf-8
import matplotlib.pyplot as plt
import numpy as np

f = [i[:-1].decode('utf-8') for i in open("input.txt", "r").readlines()]


if f[0] == '1':
    def autolabel(rects):
        for rect in rects:
            height = rect.get_height()
            plt.text(rect.get_x()+rect.get_width()/2., 1.03*height, '%s' % float(height))

    plt.xlabel(u'排序算法')
    plt.ylabel(u'运行时间(ms)')


    plt.title(u"运行时间比较（数据规模: %s， 数据类型： %s）"% (f[2], f[1]))
    xpoints = [i*(2.5/(len(f)-3)) for i in range(0, (len(f)-3)/2)]
    xlabels = [f[2*i+1] for i in range(1, (len(f)-3)/2+1)]
    ypoints = [float(f[2*i+2]) for i in range(1, (len(f)-3)/2+1)]
    plt.xticks(xpoints, xlabels)
    rect = plt.bar(left = xpoints, height = ypoints, width = 0.1, align="center")#, yerr = 0.0004)

    #plt.legend((rect,),(u"图例",))
    autolabel(rect)

    plt.show()
else:
    if f[0] == '2':
    	plt.xlabel(u'数据规模')
    	plt.ylabel(u'运行时间(ms)')
    	plt.title(u"运行时间比较（排序算法: %s， 数据类型： %s）"% (f[2], f[1]))
    	scale = [float(x.split(' ')[0]) for x in f[3:]]
    	time = [float(x.split(' ')[1]) for x in f[3:]] 
        #print [scale, time]
        plt.plot(scale, time)
        plt.show()