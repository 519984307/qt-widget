#include "qucplugin.h"

#include "gaugearcplugin.h"
#include "gaugepercentplugin.h"
#include "gaugecarplugin.h"
#include "gaugecircleplugin.h"
#include "gaugeclockplugin.h"
#include "gaugecompassplugin.h"
#include "gaugecompass2plugin.h"
#include "gaugecompasspanplugin.h"
#include "gaugedialplugin.h"
#include "gaugeminiplugin.h"
#include "gaugeplaneplugin.h"
#include "gaugeprogressplugin.h"
#include "gaugerangeplugin.h"
#include "gaugeroundplugin.h"
#include "gaugesimpleplugin.h"
#include "gaugewatchplugin.h"
#include "gaugenetplugin.h"
#include "gaugespeedplugin.h"
#include "gaugelpmplugin.h"
#include "gaugecolorplugin.h"
#include "gaugecloudplugin.h"
#include "gaugeweatherplugin.h"
#include "gaugedecibelplugin.h"
#include "gaugepanelplugin.h"
#include "gaugeeditplugin.h"

#include "progressbuttonplugin.h"
#include "progresscolorplugin.h"
#include "progresspercentplugin.h"
#include "progressroundplugin.h"
#include "progresswaitplugin.h"
#include "progresswaterplugin.h"
#include "progressthreeplugin.h"
#include "progressplayplugin.h"
#include "progressringplugin.h"
#include "progressarcplugin.h"
#include "progressshadowplugin.h"
#include "progresstipplugin.h"
#include "progresscountdownplugin.h"

#include "batteryplugin.h"
#include "lightbuttonplugin.h"
#include "lightpointplugin.h"
#include "magicmouseplugin.h"
#include "magicpenguinplugin.h"
#include "magicfishplugin.h"
#include "magicpoolplugin.h"
#include "roundcircleplugin.h"
#include "roundwidgetplugin.h"
#include "roundlogoplugin.h"
#include "switchbuttonplugin.h"
#include "oventimerplugin.h"
#include "tumblerplugin.h"
#include "tumblerdatetimeplugin.h"
#include "lunarcalendaritemplugin.h"
#include "lunarcalendarwidgetplugin.h"
#include "tiledbgplugin.h"
#include "telwidgetplugin.h"

#include "customgraphicsplugin.h"
#include "customrockerplugin.h"
#include "custompieplugin.h"
#include "customringplugin.h"
#include "customdartplugin.h"
#include "scantantanplugin.h"
#include "spiderchartplugin.h"
#include "shadowcalendarplugin.h"
#include "shadowclockplugin.h"
#include "shadowwidgetplugin.h"
#include "tasktableviewplugin.h"
#include "timeaxisplugin.h"
#include "timelineplugin.h"

#include "navbarplugin.h"
#include "navbuttonplugin.h"
#include "navlabelplugin.h"
#include "navlistviewplugin.h"
#include "navprogressplugin.h"
#include "navbuttongroupplugin.h"
#include "navtitleplugin.h"
#include "navpageplugin.h"

#include "wavebarplugin.h"
#include "wavechartplugin.h"
#include "wavedataplugin.h"
#include "wavedoubleplugin.h"
#include "wavelineplugin.h"
#include "waveplotplugin.h"
#include "wavewaterplugin.h"

#include "rulerbarplugin.h"
#include "rulerlineplugin.h"
#include "rulersliderplugin.h"
#include "rulerdoubleplugin.h"
#include "rulertempplugin.h"
#include "rulerscaleplugin.h"
#include "rulerprogressplugin.h"

#include "sliderselectplugin.h"
#include "sliderrangeplugin.h"
#include "slidertipplugin.h"

#include "barvolumeplugin.h"
#include "barvumeterplugin.h"

#include "colorcomboboxplugin.h"
#include "colorpanelbarplugin.h"
#include "colorpanelfaderplugin.h"
#include "colorpanelhsbplugin.h"
#include "colorpanelbtnplugin.h"
#include "colorbuttonplugin.h"
#include "colorstyleplugin.h"

#include "adswidgetplugin.h"
#include "adswidget2plugin.h"
#include "animationbutton1plugin.h"
#include "animationbutton2plugin.h"
#include "devicebuttonplugin.h"
#include "imageanimationplugin.h"
#include "imagecalendarplugin.h"
#include "imageclockplugin.h"
#include "imagepilotplugin.h"
#include "imagepowerplugin.h"
#include "imageswitchplugin.h"
#include "imageviewplugin.h"

#include "antlineplugin.h"
#include "lcddatetimeplugin.h"
#include "lcdnumberplugin.h"
#include "lednumberplugin.h"
#include "ledtextplugin.h"
#include "devicesizetableplugin.h"
#include "cpumemorylabelplugin.h"
#include "textmovewidgetplugin.h"
#include "panelitemplugin.h"
#include "panelwidgetplugin.h"
#include "verifiedcodeplugin.h"
#include "iconeditorplugin.h"
#include "ipaddressplugin.h"
#include "selectwidgetplugin.h"

#include "videopanelplugin.h"
#include "videoplaybackplugin.h"
#include "videowidgetplugin.h"

#include "flightadiplugin.h"
#include "flightaltplugin.h"
#include "flightasiplugin.h"
#include "flighthsiplugin.h"
#include "flightnavplugin.h"
#include "flightpfdplugin.h"
#include "flighttcplugin.h"
#include "flightvsiplugin.h"

#include "xlistwidgetplugin.h"
#include "xlistwidgetvsplugin.h"
#include "xlistwidgetvtplugin.h"
#include "xsliderplugin.h"
#include "xprogressbarplugin.h"
#include "xcomboboxplugin.h"
#include "xstackwidgetplugin.h"
#include "xtablewidgetplugin.h"

#include "ycomboboxplugin.h"
#include "yspinboxplugin.h"
#include "ydoublespinboxplugin.h"
#include "yscrollbarhplugin.h"
#include "yscrollbarvplugin.h"
#include "ylistwidgetplugin.h"
#include "ytreewidgetplugin.h"
#include "ytablewidgetplugin.h"

QucPlugin::QucPlugin(QObject *parent) : QObject(parent)
{
    widgets.append(new GaugeArcPlugin(this));
    widgets.append(new GaugePercentPlugin(this));
    widgets.append(new GaugeCarPlugin(this));
    widgets.append(new GaugeCirclePlugin(this));
    widgets.append(new GaugeClockPlugin(this));
    widgets.append(new GaugeCompassPlugin(this));
    widgets.append(new GaugeCompass2Plugin(this));
    widgets.append(new GaugeCompassPanPlugin(this));
    widgets.append(new GaugeDialPlugin(this));
    widgets.append(new GaugeMiniPlugin(this));
    widgets.append(new GaugePlanePlugin(this));
    widgets.append(new GaugeProgressPlugin(this));
    widgets.append(new GaugeRoundPlugin(this));
    widgets.append(new GaugeRangePlugin(this));
    widgets.append(new GaugeSimplePlugin(this));
    widgets.append(new GaugeWatchPlugin(this));
    widgets.append(new GaugeNetPlugin(this));
    widgets.append(new GaugeSpeedPlugin(this));
    widgets.append(new GaugeLpmPlugin(this));
    widgets.append(new GaugeColorPlugin(this));
    widgets.append(new GaugeCloudPlugin(this));
    widgets.append(new GaugeWeatherPlugin(this));
    widgets.append(new GaugeDecibelPlugin(this));
    widgets.append(new GaugePanelPlugin(this));
    widgets.append(new GaugeEditPlugin(this));

    widgets.append(new ProgressButtonPlugin(this));
    widgets.append(new ProgressColorPlugin(this));
    widgets.append(new ProgressPercentPlugin(this));
    widgets.append(new ProgressRoundPlugin(this));
    widgets.append(new ProgressWaitPlugin(this));
    widgets.append(new ProgressWaterPlugin(this));
    widgets.append(new ProgressThreePlugin(this));
    widgets.append(new ProgressPlayPlugin(this));
    widgets.append(new ProgressRingPlugin(this));
    widgets.append(new ProgressArcPlugin(this));
    widgets.append(new ProgressShadowPlugin(this));
    widgets.append(new ProgressTipPlugin(this));
    widgets.append(new ProgressCountDownPlugin(this));

    widgets.append(new BatteryPlugin(this));
    widgets.append(new LightButtonPlugin(this));
    widgets.append(new LightPointPlugin(this));    
    widgets.append(new MagicMousePlugin(this));
    widgets.append(new MagicPenguinPlugin(this));
    widgets.append(new MagicFishPlugin(this));
    widgets.append(new MagicPoolPlugin(this));
    widgets.append(new RoundCirclePlugin(this));
    widgets.append(new RoundWidgetPlugin(this));
    widgets.append(new RoundLogoPlugin(this));
    widgets.append(new SwitchButtonPlugin(this));
    widgets.append(new OvenTimerPlugin(this));
    widgets.append(new TumblerPlugin(this));
    widgets.append(new TumblerDateTimePlugin(this));
    widgets.append(new LunarCalendarItemPlugin(this));
    widgets.append(new LunarCalendarWidgetPlugin(this));
    widgets.append(new TiledBgPlugin(this));
    widgets.append(new TelWidgetPlugin(this));

    widgets.append(new CustomGraphicsPlugin(this));
    widgets.append(new CustomRockerPlugin(this));
    widgets.append(new CustomPiePlugin(this));
    widgets.append(new CustomRingPlugin(this));
    widgets.append(new CustomDartPlugin(this));
    widgets.append(new ScanTanTanPlugin(this));
    widgets.append(new SpiderChartPlugin(this));
    widgets.append(new ShadowCalendarPlugin(this));
    widgets.append(new ShadowClockPlugin(this));
    widgets.append(new ShadowWidgetPlugin(this));
    widgets.append(new TaskTableViewPlugin(this));
    widgets.append(new TimeAxisPlugin(this));
    widgets.append(new TimeLinePlugin(this));

    widgets.append(new NavBarPlugin(this));
    widgets.append(new NavButtonPlugin(this));
    widgets.append(new NavLabelPlugin(this));
    widgets.append(new NavListViewPlugin(this));
    widgets.append(new NavProgressPlugin(this));
    widgets.append(new NavButtonGroupPlugin(this));
    widgets.append(new NavTitlePlugin(this));
    widgets.append(new NavPagePlugin(this));

    widgets.append(new WaveBarPlugin(this));
    widgets.append(new WaveChartPlugin(this));
    widgets.append(new WaveDataPlugin(this));
    widgets.append(new WaveDoublePlugin(this));
    widgets.append(new WaveLinePlugin(this));
    widgets.append(new WavePlotPlugin(this));
    widgets.append(new WaveWaterPlugin(this));

    widgets.append(new RulerBarPlugin(this));
    widgets.append(new RulerLinePlugin(this));
    widgets.append(new RulerSliderPlugin(this));
    widgets.append(new RulerDoublePlugin(this));
    widgets.append(new RulerTempPlugin(this));
    widgets.append(new RulerScalePlugin(this));
    widgets.append(new RulerProgressPlugin(this));

    widgets.append(new SliderSelectPlugin(this));
    widgets.append(new SliderRangePlugin(this));
    widgets.append(new SliderTipPlugin(this));

    widgets.append(new BarVolumePlugin(this));
    widgets.append(new BarVUMeterPlugin(this));

    widgets.append(new ColorComboBoxPlugin(this));
    widgets.append(new ColorPanelBarPlugin(this));
    widgets.append(new ColorPanelFaderPlugin(this));
    widgets.append(new ColorPanelHSBPlugin(this));
    widgets.append(new ColorPanelBtnPlugin(this));
    widgets.append(new ColorButtonPlugin(this));
    widgets.append(new ColorStylePlugin(this));

    widgets.append(new AdsWidgetPlugin(this));
    widgets.append(new AdsWidget2Plugin(this));
    widgets.append(new AnimationButton1Plugin(this));
    widgets.append(new AnimationButton2Plugin(this));
    widgets.append(new DeviceButtonPlugin(this));
    widgets.append(new ImageAnimationPlugin(this));
    widgets.append(new ImageCalendarPlugin(this));
    widgets.append(new ImageClockPlugin(this));
    widgets.append(new ImagePilotPlugin(this));
    widgets.append(new ImagePowerPlugin(this));
    widgets.append(new ImageSwitchPlugin(this));
    widgets.append(new ImageViewPlugin(this));

    widgets.append(new AntLinePlugin(this));
    widgets.append(new LcdDateTimePlugin(this));
    widgets.append(new LcdNumberPlugin(this));
    widgets.append(new LedNumberPlugin(this));
    widgets.append(new LedTextPlugin(this));
    widgets.append(new DeviceSizeTablePlugin(this));
    widgets.append(new CpuMemoryLabelPlugin(this));
    widgets.append(new TextMoveWidgetPlugin(this));
    widgets.append(new PanelItemPlugin(this));
    widgets.append(new PanelWidgetPlugin(this));
    widgets.append(new VerifiedCodePlugin(this));
    widgets.append(new IconEditorPlugin(this));
    widgets.append(new IPAddressPlugin(this));
    widgets.append(new SelectWidgetPlugin(this));

    widgets.append(new VideoPanelPlugin(this));
    widgets.append(new VideoPlaybackPlugin(this));
    widgets.append(new VideoWidgetPlugin(this));

    widgets.append(new FlightADIPlugin(this));
    widgets.append(new FlightALTPlugin(this));
    widgets.append(new FlightASIPlugin(this));
    widgets.append(new FlightHSIPlugin(this));
    widgets.append(new FlightNAVPlugin(this));
    widgets.append(new FlightPFDPlugin(this));
    widgets.append(new FlightTCPlugin(this));
    widgets.append(new FlightVSIPlugin(this));

    widgets.append(new XListWidgetPlugin(this));
    widgets.append(new XListWidgetVSPlugin(this));
    widgets.append(new XListWidgetVTPlugin(this));
    widgets.append(new XSliderPlugin(this));
    widgets.append(new XProgressBarPlugin(this));
    widgets.append(new XComboBoxPlugin(this));
    widgets.append(new XStackWidgetPlugin(this));
    widgets.append(new XTableWidgetPlugin(this));

    widgets.append(new YComboBoxPlugin(this));
    widgets.append(new YSpinBoxPlugin(this));
    widgets.append(new YDoubleSpinBoxPlugin(this));
    widgets.append(new YScrollBarHPlugin(this));
    widgets.append(new YScrollBarVPlugin(this));
    widgets.append(new YListWidgetPlugin(this));
    widgets.append(new YTreeWidgetPlugin(this));
    widgets.append(new YTableWidgetPlugin(this));
}

QList<QDesignerCustomWidgetInterface *> QucPlugin::customWidgets() const
{
    return widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(allcontrolplugin, QucPlugin)
#endif // QT_VERSION < 0x050000
